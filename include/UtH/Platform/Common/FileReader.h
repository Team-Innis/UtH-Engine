/***
 * Filereader for linux and windows
 **/
#pragma once
#ifndef FILEREADER_H
#define FILEREADER_H

#include <cstdio>
#include <physfs/physfs.h>
#include <UtH/Platform/BinaryData.hpp>

namespace uth
{
	class FileReader
	{
	public:
		FileReader();
		FileReader(const char* path);
		~FileReader();

		void OpenFile(const char* path);
        void CloseFile();
		int GetFileSize();

		// Move the file pointer by offset from origin(defaults to current location)
		// see SEEK_SET, SEEK_CUR and SEEK_END
		bool FileSeek(int offset, int origin = SEEK_CUR);

		// Read a 'count' ammount of 'blockSize' sized blocks of data from file to buffer
		// Buffer is a pointer to the first element of an array
		// Also sets the file pointer to the end of read block
		bool ReadBytes(void* buffer, unsigned int count, unsigned int blockSize = 1);

		// Read whole file
		const BINARY_DATA ReadBinary();
		const char* ReadText();

		static bool isCompressed;
	private:
		std::FILE* file;
		PHYSFS_file* cFile;

		
	};
}

#endif