#include <UtH/Platform/FileReader.h>
#include <cstdlib> //malloc
#include <UtH/Platform/Debug.hpp>

using namespace uth;

AAssetManager* FileReader::m_manager = nullptr;

FileReader::FileReader()
	: m_asset(nullptr)
{ }
FileReader::FileReader(const char* path)
{
	OpenFile(path);
}
FileReader::~FileReader()
{
	CloseFile();
}

void FileReader::OpenFile(const char* path)
{
	m_asset = AAssetManager_open(m_manager, path,2);
	m_length = AAsset_getLength(m_asset);
}
void FileReader::CloseFile()
{
	//AAsset_close(m_asset);
}
int FileReader::GetFileSize()
{
	return m_length;
}

bool FileReader::FileSeek(int offset, int origin)
{
	if(AAsset_seek(m_asset, offset, origin) != -1)
		return true;
	return false;
}

bool FileReader::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
	if(AAsset_read(m_asset, buffer, count * blockSize) >= 0)
		return true;
	return false;
}

const BINARY_DATA FileReader::ReadBinary()
{
	BINARY_DATA retVal(GetFileSize());
	if(!ReadBytes(retVal.ptr(),retVal.size()))
		return BINARY_DATA();
	return retVal;
}

const std::string FileReader::ReadText()
{
	int size = GetFileSize();
	char* buffer = new char[size];
	ReadBytes(buffer, size);

	std::string str(buffer, size);
	delete[] buffer;
	return str;
}

