#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>

#include <cstdlib> //malloc
#include <cstdio>
#include <sys/stat.h>
#include <iostream>

using namespace uth;

AAssetManager* FileManager::m_manager = nullptr;

FileManager::FileManager()
	//:m_file(nullptr),
	:m_stream(NULL),
	 m_asset(nullptr),
	 m_length(0)
{ }
FileManager::FileManager(const std::string& path, const Location loca /*= Location::ASSET*/)
	//:m_file(nullptr),
	: m_stream(NULL),
	 m_asset(nullptr),
	 m_length(0)
{
	OpenFile(path,loca);
}
FileManager::~FileManager()
{
	CloseFile();
}

void FileManager::OpenFile(const std::string& path, const Location loca /*= Location::ASSET*/)
{
	errno = 0;
	if (loca == Location::ASSET)
	{
		m_asset = AAssetManager_open(m_manager, path.c_str(), 2);
		if (m_asset != nullptr)
		{
			m_length = AAsset_getLength(m_asset);
		}
	}
	else if (loca == Location::INTERNAL || loca == Location::EXTERNAL)
	{
		std::string truePath;

		if (loca == Location::INTERNAL)
		{
			//TODO find which sdcard
			truePath = "/sdcard/" + path;
		}
		else
			truePath = uthAndroidEngine.internalPath + "/" + path;

		m_stream.open(truePath, std::ios::in | std::ios::ate);
		if (m_stream.is_open())
		{
			m_length = m_stream.tellg();
			char* memblock = new char[m_length+1];
			m_stream.seekg(0, std::ios::beg);
			m_stream.read(memblock, m_length);
			m_stream.seekg(0, std::ios::beg);
			memblock[m_length] = 0;
			delete[] memblock;
		}
		else
		{
			WriteError("errno %s with file %s", strerror(errno), truePath.c_str());
		}
	}
}
void FileManager::CloseFile()
{
	//AAsset_close(m_asset);
	if (m_stream.is_open())
		m_stream.close();
}
int FileManager::GetFileSize()
{
	return m_length;
}

bool FileManager::FileSeek(int offset, int origin)
{
	if(AAsset_seek(m_asset, offset, origin) != -1)
		return true;
	return false;
}

bool FileManager::ReadBytes(void* b, unsigned int count, unsigned int blockSize)
{
	char* buffer = (char*)b;

	if (m_asset && AAsset_read(m_asset, buffer, count * blockSize) >= 0)
	{
		return true;
	}
	else if (m_stream && m_stream.is_open())
	{
		std::vector<char> data;
		data.resize(count*blockSize);
		m_stream.read(&data[0], data.size());
		memcpy(buffer, &data[0], data.size());
		return true;
	}
	else
		WriteLog("Readbytes failed:  %s", strerror(errno));
	return false;
}

const BINARY_DATA FileManager::ReadBinary()
{
	BINARY_DATA retVal(GetFileSize());
	if(!ReadBytes(retVal.ptr(),retVal.size()))
		return BINARY_DATA();
	return retVal;
}

const std::string FileManager::ReadText()
{
	const int size = GetFileSize();
	char* buffer = new char[size+1];
	ReadBytes(buffer, size);
	buffer[size] = 0;
	std::string str;
	str += buffer;
	//WriteLog("readtext %s %s", str.c_str(), buffer);
	delete[] buffer;
	return str;
}

void FileManager::WriteToFile(const std::string& filename, const std::string& data,
	const Location loca /*= Location::INTERNAL*/)
{
	errno = 0;
	std::string dataPath;
	std::string splitName;
	if (loca == Location::EXTERNAL)
	{
		size_t temp = filename.rfind("/");
		if (temp != -1)
		{
			// find correct sdcard
			dataPath = ("/sdcard/") + filename.substr(0, temp+1);
			splitName = filename.substr(temp+1, filename.length() - temp);
		}
		else
		{
			dataPath = ("/sdcard/");
			splitName = filename;
		}
	}
	else if (loca == Location::INTERNAL)
 	{
		size_t temp = filename.rfind("/");
		if (temp != -1)
		{
			dataPath = (uthAndroidEngine.internalPath + "/") + filename.substr(0, temp + 1);
			splitName = filename.substr(temp + 1, filename.length() - temp);
		}
		else
		{
			dataPath = (uthAndroidEngine.internalPath + "/");
			splitName = filename;
		}
 	}
	else
	{
		WriteError("Couldn't write to %d", loca);
	}

	struct stat sb;
	int32_t res = stat(dataPath.c_str(), &sb);

	if (0 == res && sb.st_mode & S_IFDIR)
	{
		WriteLog("%s dir already in app's internal data storage.", dataPath.c_str());

	}
	if (ENOENT == errno)
	{
		res = mkdir(dataPath.c_str(), 0777);
		if (res == 0)
			uth::WriteLog("Creating data folder succeeded!");
		else
			uth::WriteError("Creating data folder failed with %d!", strerror(errno));

	}
	errno = 0;

	dataPath += splitName;

	if (m_stream.is_open())
		m_stream.close();

	m_stream.open(dataPath, std::ios::out | std::ios::trunc);
	if (m_stream.is_open())
	{
		m_stream << data;
		m_stream.close();
		WriteLog("Data at %s is: %s",dataPath.c_str(), data.c_str());
	}
	else
		WriteError("File stream error: %s", strerror(errno));
}

void FileManager::WriteToFile(const std::string& filename, const BINARY_DATA& data)
{
	std::string dataPath(uthAndroidEngine.internalPath + "/");

	struct stat sb;
	int32_t res = stat(dataPath.c_str(), &sb);

	if (0 == res && sb.st_mode & S_IFDIR)
	{
		WriteLog("%s dir already in app's internal data storage.", dataPath.c_str());
	}
	else if (ENOENT == errno)
	{
		res = mkdir(dataPath.c_str(), 0770);
		if (!res)
			uth::WriteLog("Creating data folder succeeded!");
		else
			uth::WriteError("Creating data folder failed with %d!", res);

	}

	dataPath += filename;
	std::FILE* file = std::fopen(dataPath.c_str(), "w+");
	if (file != NULL)
	{
		std::fwrite(&data, sizeof(unsigned char), data.size(), file);
		std::fflush(file);
		std::fclose(file);
	}
	else
	{
		WriteError("Writing to file failed! File couldn't be opened for writing.");
	}
}

AAsset* FileManager::loadSound(const std::string& fileName)
{
	return AAssetManager_open(m_manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
}

int64_t FileManager::getAssetLength(void* asset)
{
	return AAsset_getLength((AAsset*)asset);
}

int64_t FileManager::seekAsset(int64_t offset, int whence, void* asset)
{
	return AAsset_seek((AAsset*)asset, offset, whence);
}

int64_t FileManager::readAsset(void* buffer, int64_t count, void* asset)
{
	return AAsset_read((AAsset*)asset, buffer, count);
}

int64_t FileManager::tellAsset(void* asset)
{
	return AAsset_seek((AAsset*)asset, 0, SEEK_CUR);
}