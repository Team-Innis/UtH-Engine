#import <Foundation/Foundation.h>

#include <UtH/Platform/iOS/FileManager.h>

using namespace uth;

FileManager::FileManager()
{
    NSString* str = [[NSBundle mainBundle] executablePath];
    
    PHYSFS_init(str.UTF8String);
    PHYSFS_addToSearchPath("assets.uth", 1);
    PHYSFS_addToSearchPath("assets.zip", 1);
}

FileManager::FileManager(const std::string& path, const Location)
    : FileManager()
{
    OpenFile(path);
}

FileManager::~FileManager()
{
    PHYSFS_deinit();
}

void FileManager::OpenFile(const std::string& path, const Location)
{
    const int result = PHYSFS_exists(path.c_str());
    assert(result);
    
    if(m_file != nullptr)
        PHYSFS_close(m_file);
    
    m_file = PHYSFS_openRead(path.c_str());
}

void FileManager::CloseFile()
{
    PHYSFS_close(m_file);
    m_file = nullptr;
}

int  FileManager::GetFileSize()
{
    return static_cast<int>(PHYSFS_fileLength(m_file));
}

// Move the file pointer by offset from origin(defaults to beginning of file)
// see SEEK_SET, SEEK_CUR and SEEK_END
bool FileManager::FileSeek(int offset, int origin)
{
    if(m_file != nullptr)
    {
        if(origin == 1)
        {
            origin = static_cast<int>(PHYSFS_tell(m_file));
            offset += origin;
        }
        if(PHYSFS_seek(m_file, offset) == 1)
            return true;
    }
    
    return true;
}

// Read a 'count' ammount of 'blockSize' sized blocks of data from file to buffer
// Buffer is a pointer to the first element of an array
// Also sets the file pointer to the end of read block
bool FileManager::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize)
{
    if(m_file != nullptr)
    {
        if(PHYSFS_read(m_file, buffer, blockSize, count) == count)
            return true;
    }
    
    return true;
}

// Returns the content of whole file as binary data
const BINARY_DATA FileManager::ReadBinary()
{
    BINARY_DATA retVal(GetFileSize());
    if(!ReadBytes(retVal.ptr(), static_cast<unsigned int>(retVal.size())))
        return BINARY_DATA();
    return retVal;
}

// Returns the content of the whole file as text
const std::string FileManager::ReadText()
{
    int size = GetFileSize();
    char* buffer = new char[size];
    ReadBytes(buffer, size);
    
    std::string str(buffer, size);
    delete[] buffer;
    return str;
}