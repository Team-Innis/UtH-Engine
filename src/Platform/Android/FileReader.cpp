#include <UtH/Platform/FileReader.hpp>

using namespace uth;

FileReader::FileReader()
{

}

FileReader::FileReader(const char* path)
{

}

FileReader::~FileReader()
{

}

void FileReader::OpenFile(const char* path)
{

}

int FileReader::GetFileSize()
{

}

bool FileReader::FileSeek(int offset, int origin = SEEK_CUR)
{

}

bool FileReader::ReadBytes(void* buffer, unsigned int count, unsigned int blockSize = 1)
{

}


void* FileReader::ReadBinary()
{

}

const char* FileReader::ReadText()
{

}
