#include <UtH/Platform/FileReader.h>
#include <cassert>
#include <cstdlib>

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
	fclose(file);
}


// Public

void FileReader::OpenFile(const char* path)
{
	file = fopen(path, "rb");
	assert(file != NULL);
}

int FileReader::GetFileSize()
{
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);

	return size;
}

bool FileReader::FileSeek(int offset, int origin)
{
	if(file != NULL)
	{
		if(fseek(file, offset, origin) == 0) // Returns 0 on succesful read
			return true;
	}
	return false;
}

bool FileReader::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
	if(file != NULL)
	{
		if(fread(buffer, blockSize, count, file) == count)
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