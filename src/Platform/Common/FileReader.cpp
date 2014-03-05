#include <UtH/Platform/FileReader.h>
#include <cassert>
#include <cstdlib>
#include <string>

using namespace uth;

FileReader::FileReader()
	: file(NULL)
{}

FileReader::FileReader(const char* path)
{
	OpenFile(path);
}

FileReader::~FileReader()
{
	std::fclose(file);
}


// Public

void FileReader::OpenFile(const char* path)
{
	std::string temp_path = "assets/";
	temp_path += path;
	file = std::fopen(temp_path.c_str(), "rb");
	assert(file != NULL);
}

int FileReader::GetFileSize()
{
	std::fseek(file, 0, SEEK_END);
	int size = std::ftell(file);
	std::fseek(file, 0, SEEK_SET);

	return size;
}

bool FileReader::FileSeek(int offset, int origin)
{
	if(file != NULL)
	{
		if(std::fseek(file, offset, origin) == 0) // Returns 0 on succesful read
			return true;
	}
	return false;
}

bool FileReader::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
	if(file != NULL)
	{
		if(std::fread(buffer, blockSize, count, file) == count)
			return true;		
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