#include <UtH/Platform/FileReader.h>
#include <cstdlib> //malloc

using namespace uth;

AAssetManager* FileReader::m_manager = NULL;

FileReader::FileReader()
	: m_asset(NULL)
{ }

FileReader::FileReader(const char* path)
{
	OpenFile(path);
}

FileReader::~FileReader()
{
	AAsset_close(m_asset);
}

void FileReader::OpenFile(const char* path)
{
	m_asset = AAssetManager_open(m_manager, path,2);
	m_length = AAsset_getLength(m_asset);
}

int FileReader::GetFileSize()
{
	return m_length;
}

bool FileReader::FileSeek(int offset, int origin)
{
	if(AAsset_seek(m_asset, offset, origin) != 1)
		return true;
	return false;
}

bool FileReader::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
	if(AAsset_read(m_asset, buffer, count * blockSize) >= 0)
		return true;
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