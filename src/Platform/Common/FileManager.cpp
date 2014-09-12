#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Debug.hpp>

#include <cassert>
#include <cstdlib> // malloc
#include <string>

using namespace uth;

bool FileManager::isCompressed = false;

FileManager::FileManager()
	: file(nullptr),
	cFile(nullptr)
{
	if(isCompressed)
		PHYSFS_init(nullptr);
}
FileManager::FileManager(const std::string& path)
{
	if(isCompressed)
		PHYSFS_init(nullptr);

	OpenFile(path);
}
FileManager::~FileManager()
{
	CloseFile();
}


// Public
void FileManager::OpenFile(const std::string& path)
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
		std::string temp_path = "assets/";
		temp_path += path;
		file = std::fopen(temp_path.c_str(), "rb");
		if (file == nullptr)
		{
			file = std::fopen(path.c_str(), "rb");
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


void FileManager::WriteToFile(const std::string& filename, const std::string& data)
{
	std::FILE* file = std::fopen(filename.c_str(), "w+");
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
	std::FILE* file = std::fopen(filename.c_str(), "w+");
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