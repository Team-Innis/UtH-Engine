#include <UtH/Platform/FileManager.hpp>
#include <cstdlib> //malloc
#include <UtH/Platform/Debug.hpp>

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