#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>

#include <cstdlib> //malloc
#include <cstdio>
#include <sys/stat.h>

using namespace uth;

AAssetManager* FileManager::m_manager = nullptr;

FileManager::FileManager()
	: m_asset(nullptr)
{ }
FileManager::FileManager(const std::string& path)
{
	OpenFile(path);
}
FileManager::~FileManager()
{
	CloseFile();
}

void FileManager::OpenFile(const std::string& path)
{
	m_asset = AAssetManager_open(m_manager, path.c_str(),2);
	m_length = AAsset_getLength(m_asset);
}
void FileManager::CloseFile()
{
	//AAsset_close(m_asset);
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

bool FileManager::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
	if(AAsset_read(m_asset, buffer, count * blockSize) >= 0)
		return true;
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
	int size = GetFileSize();
	char* buffer = new char[size];
	ReadBytes(buffer, size);

	std::string str(buffer, size);
	delete[] buffer;
	return str;
}

void FileManager::WriteToFile(const std::string& filename, const std::string& data)
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
		std::fputs(data.c_str(), file);
		std::fflush(file);
		std::fclose(file);
	}
	else
	{
		WriteError("Writing to file failed! File couldn't be opened for writing.");
	}
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