#include <UtH/Platform/FileReader.h>
#include <cassert>
#include <cstdlib>
#include <string>
#include <UtH\Platform\Debug.hpp>

using namespace uth;

bool FileReader::isCompressed = false;
FileReader::FileReader()
	: file(NULL),
	  cFile(NULL)
{
	if(isCompressed)
		PHYSFS_init(NULL);
}

FileReader::FileReader(const char* path)
{
	if(isCompressed)
		PHYSFS_init(NULL);

	OpenFile(path);
}

FileReader::~FileReader()
{
	if(PHYSFS_isInit())
	{
		PHYSFS_close(cFile);
		PHYSFS_deinit();
	}
	else
    {
		WriteLog("closing file\n");
        if (file != NULL)
		    fclose(file);
		WriteLog("file closed\n");
    }
}


// Public
void FileReader::OpenFile(const char* path)
{
	if(PHYSFS_isInit())
	{		
		PHYSFS_addToSearchPath("assets.uth",1);
		assert(PHYSFS_exists(path));

		if(cFile != NULL)
			PHYSFS_close(cFile);

		cFile = PHYSFS_openRead(path);
		assert(cFile != NULL);
	}
	else
	{
		std::string temp_path = "assets/";
		temp_path += path;
		file = std::fopen(temp_path.c_str(), "rb");
		assert(file != NULL);
	}
}

int FileReader::GetFileSize()
{
	int size;
	if(PHYSFS_isInit())
	{
		size = PHYSFS_fileLength(cFile);
		return size;
	}
	else
	{
		fseek(file, 0, SEEK_END);
		size = ftell(file);
		fseek(file, 0, SEEK_SET);
	}
	return size;
}

bool FileReader::FileSeek(int offset, int origin)
{
	if(PHYSFS_isInit())
	{
		if(cFile != NULL)
		{
			if(origin == 1)
			{
				origin = PHYSFS_tell(cFile);
				offset += origin;
			}
			if(PHYSFS_seek(cFile, offset) == 1)
				return true;
		}
	}
	else
	{
		if(file != NULL)
		{
			if(std::fseek(file, offset, origin) == 0) // Returns 0 on succesful read
				return true;
		}
	}
	return false;
}

bool FileReader::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
	if(PHYSFS_isInit())
	{
		if(cFile != NULL)
		{
			if(PHYSFS_read(cFile, buffer, blockSize, count) == count)
				return true;
		}
	}
	else
	{
		if(file != NULL)
		{
			if(std::fread(buffer, blockSize, count, file) == count)
				return true;		
		}
	}
	return false;
}

void* FileReader::ReadBinary()
{
	int size = GetFileSize();
	void* buffer;
	buffer = malloc(size);
	ReadBytes(buffer, size);	
	
	return buffer;
}

const char* FileReader::ReadText()
{
	
	int size = GetFileSize();
	char* buffer = new char[size];
	ReadBytes(buffer, size);

	buffer[size] = 0; // Null terminate the string

	return buffer;	
}