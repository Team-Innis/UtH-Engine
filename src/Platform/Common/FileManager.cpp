#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Debug.hpp>

#include <cassert>
#include <cstdlib> // malloc
#include <string>

#ifdef UTH_SYSTEM_WINDOWS
	#include <direct.h> // _mkdir
    #define mkdir _mkdir
#endif

using namespace uth;

bool FileManager::isCompressed = false;

FileManager::FileManager()
	: file(nullptr),
	cFile(nullptr)
{
	if(isCompressed)
		PHYSFS_init(nullptr);
}

FileManager::FileManager(const std::string& path, const Location loca /*= Location::ASSET*/)
{
	if(isCompressed)
		PHYSFS_init(nullptr);

	OpenFile(path, loca);
}

FileManager::~FileManager()
{
	CloseFile();
}

// Public
void FileManager::OpenFile(const std::string& path, const Location loca /*=LOCATION::ASSET*/)
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
		file = std::fopen(temp_path.c_str(), "rb");
		if (file == nullptr)
		{
			WriteLog("file not found from %s", temp_path.c_str());
			file = std::fopen(path.c_str(), "rb");
			if (file == nullptr)
				WriteLog("file not found from %s", path.c_str());
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

void FileManager::WriteToFile(const std::string& filename, const std::string& data,
	const Location loca /*=Location::INTERNAL*/)
{
	std::string temp_path;
	if (loca == Location::EXTERNAL)
	{
		temp_path = "external/";
		mkdir(temp_path.c_str());
	}
	else if (loca == Location::INTERNAL)
	{
		temp_path = "internal/";
		mkdir(temp_path.c_str());
	}
	else
		WriteError("No such file location available %d", loca);

	temp_path += filename;

	std::FILE* file = std::fopen(temp_path.c_str(), "w+");
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