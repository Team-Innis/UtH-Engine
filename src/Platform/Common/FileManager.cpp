#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Debug.hpp>

#include <cassert>
#include <cstdlib> // malloc
#include <string>
#include <vector>

#ifdef UTH_SYSTEM_WINDOWS
	#include <direct.h> // _mkdir
#endif

#include <sys/types.h>
#include <sys/stat.h>

using namespace uth;

bool FileManager::isCompressed = false;

void ensureDirectoryExists(const std::string& path);

FileManager::FileManager()
	: file(nullptr),
	cFile(nullptr),
    m_writable(false)
{
	if(isCompressed)
		PHYSFS_init(nullptr);
}

FileManager::FileManager(const std::string& path, const Location loca, bool isWritable)
    : FileManager()
{
	OpenFile(path, loca, isWritable);
}

FileManager::~FileManager()
{
	CloseFile();
}

// Public
void FileManager::OpenFile(const std::string& path, const Location loca, bool isWritable)
{
	//CloseFile();

	if(PHYSFS_isInit())
	{		
		PHYSFS_addToSearchPath("assets.uth",1);
		const int result = PHYSFS_exists(path.c_str());
		assert(result);

		if(cFile != nullptr)
			PHYSFS_close(cFile);

		cFile = PHYSFS_openRead(path.c_str());
		assert(cFile != nullptr);
	}
	else
	{
		std::string temp_path;
		if (loca == Location::ASSET)
			temp_path = "assets/";
		else if (loca == Location::EXTERNAL)
			temp_path = "external/";
		else if (loca == Location::INTERNAL)
			temp_path = "internal/";
		else
			WriteError("No such file location available %d", loca);

		temp_path += path;

        if (loca != Location::ASSET)
            ensureDirectoryExists(temp_path);

        if (!isWritable)
		    file = std::fopen(temp_path.c_str(), "r+b");
        else
		{
            m_writable = true;
            file = std::fopen(temp_path.c_str(), "w+b");
            if (file == nullptr)
                WriteError("Cannot open file %s", temp_path.c_str());
		}
		assert(file != nullptr);
	}
}

void FileManager::CloseFile()
{
	if(PHYSFS_isInit())
	{
		PHYSFS_close(cFile);
		PHYSFS_deinit();
	}
	else if (file)
	{
		std::fclose(file);
		file = nullptr;
	}
}

int FileManager::GetFileSize()
{
	int size;
	if(PHYSFS_isInit())
	{
		size = static_cast<int>(PHYSFS_fileLength(cFile));
		return size;
	}
	else
	{
		std::fseek(file, 0, SEEK_END);
		size = std::ftell(file);
		std::fseek(file, 0, SEEK_SET);
	}
	return size;
}

bool FileManager::FileSeek(int offset, int origin)
{
	if(PHYSFS_isInit())
	{
		if(cFile != nullptr)
		{
			if(origin == 1)
			{
				origin = static_cast<int>(PHYSFS_tell(cFile));
				offset += origin;
			}
			if(PHYSFS_seek(cFile, offset) == 1)
				return true;
		}
	}
	else
	{
		if(file != nullptr)
		{
			if(std::fseek(file, offset, origin) == 0) // Returns 0 on succesful read
				return true;
		}
	}
	return false;
}

bool FileManager::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
	if(PHYSFS_isInit())
	{
		if(cFile != nullptr)
		{
			if(PHYSFS_read(cFile, buffer, blockSize, count) == count)
				return true;
		}
	}
	else
	{
		if(file != nullptr)
		{
			if(std::fread(buffer, blockSize, count, file) == count)
				return true;
		}
	}
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

void FileManager::WriteString(const std::string& data)
{
    if (m_writable)
        std::fwrite(data.c_str(), sizeof(char), data.length(), file);
    else
        WriteError("Current file is not opened as writable");
}

void ensureDirectoryExists(const std::string& path)
{
    std::vector<std::string> dirs;

    size_t pos = path.find("/", 1);
    size_t lastPos = 0;

    while (pos != std::string::npos)
    {
        dirs.push_back(path.substr(lastPos, pos - lastPos));
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

        if (!(s.st_mode & S_IFDIR) || ret != 0)
        {
            WriteLog("Creating dir %s", testPath.c_str());


            int status;
            // Try to create the directory
            #ifdef UTH_SYSTEM_WINDOWS
            status = _mkdir(testPath.c_str());
            #else
            status = mkdir(testPath.c_str(), 0777);
            #endif // UTH_SYSTEM_WINDOWS

            if (status == -1)
                WriteError("Error: %s when creating directory: %s", strerror(errno),
                testPath.c_str());
        }
    }
}