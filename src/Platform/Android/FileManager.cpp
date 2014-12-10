#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <cstdlib> //malloc
#include <cstdio>
#include <sys/stat.h>
#include <iostream>

using namespace uth;

AAssetManager* FileManager::m_manager = nullptr;

bool ensureDirectoryExists(const std::string& path);

FileManager::FileManager()
	//:m_file(nullptr),
	:m_stream(NULL),
	 m_asset(nullptr),
     m_writable(false)
{ }

FileManager::FileManager(const std::string& path, const Location loca, bool isWritable)
	//:m_file(nullptr),
	: m_stream(NULL),
	 m_asset(nullptr),
     m_writable(false)
{
	OpenFile(path, loca, isWritable);
}

FileManager::~FileManager()
{
	CloseFile();
}

bool FileManager::OpenFile(const std::string& path, const Location loca, bool isWritable)
{
    // We can safely ignore isWritable because it doesn't matter here

	errno = 0;
	if (loca == Location::ASSET)
	{
		m_asset = AAssetManager_open(m_manager, path.c_str(), 2);
        return true;
	}
	else if (loca == Location::INTERNAL || loca == Location::EXTERNAL)
	{
		std::string truePath;

		if (loca == Location::EXTERNAL)
		{
			struct stat sb;
			int32_t res = stat("/sdcard/", &sb);
			if (0 == res && sb.st_mode & S_IFDIR)
			{
				truePath = "/sdcard/" + path;
			}
			else
			{
				res = stat("/sdcard0/", &sb);
				if (0 == res && sb.st_mode & S_IFDIR)
					truePath = "/sdcard0/" + path;
				else
					truePath = "/sdcard1/" + path;
			}
		}
		else
			truePath = uthAndroidEngine.internalPath + "/" + path;

        if (!ensureDirectoryExists(truePath))
			return false;

        if (isWritable)
        {
            m_stream.open(truePath, std::ios::in | std::ios::out | std::ios::trunc);
            m_writable = true;
        }
        else
            m_stream.open(truePath, std::ios::in);

        // First try to create the file if it does not exist
        if (isWritable && !m_stream.is_open())
        {
            // Try creating the file
            m_stream.clear();
            m_stream.open(truePath, std::ios::out);
            m_stream.close();
            m_stream.open(truePath, std::ios::in | std::ios::out);
        }

        // If it's still not open then we have a problem
        if (!m_stream.is_open())
		{
			WriteError("errno %s with file %s", strerror(errno), truePath.c_str());
			return false;
		}
	}
	return true;
}

void FileManager::CloseFile()
{
	//AAsset_close(m_asset);
	if (m_stream.is_open())
		m_stream.close();
}

int FileManager::GetFileSize()
{
    if (m_asset != nullptr)
    {
        return AAsset_getLength(m_asset);
    }

    m_stream.seekg(0, m_stream.end);
    int length = m_stream.tellg();
    m_stream.seekg(0, m_stream.beg);

	return length;
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

void uth::FileManager::WriteString(const std::string& data)
{
    if (!m_stream.is_open())
    {
        WriteError("No file is open");
        return;
    }
    else if (!m_writable)
        WriteError("File not writable");

    WriteLog("Writing: %s", data.c_str());

    m_stream << data;
}

void uth::FileManager::WriteBinary(const BINARY_DATA& data)
{
    if (!m_stream.is_open())
    {
        WriteError("No file is open");
        return;
    }
    else if (!m_writable)
        WriteError("File not writable");

    m_stream.write(reinterpret_cast<const char *>(data.ptr()), data.size());
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

bool ensureDirectoryExists(const std::string& path)
{
    std::vector<std::string> dirs;

    size_t pos = path.find("/", 1);
    size_t lastPos = 0;

    while (pos != std::string::npos)
    {
        dirs.push_back(path.substr(lastPos, pos-lastPos));
        lastPos = pos;
        pos = path.find("/", lastPos + 1);
    }

    // Check the dirs actually exist
    std::string testPath;
    for (int i = 0; i < dirs.size(); ++i)
    {
        testPath += dirs.at(i);

        struct stat s;

        int ret = stat(testPath.c_str(), &s);

        if (!S_ISDIR(s.st_mode) || ret != 0)
        {
            // Try to create the directory
            int status = mkdir(testPath.c_str(), 0777);
			if (status == -1)
			{
				WriteError("Error: %s when creating directory: %s", strerror(errno),
					testPath.c_str());
				return false;
			}
        }
    }
	return true;
}
