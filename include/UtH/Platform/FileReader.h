#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>

namespace uth
{
	class FileReader
	{
	public:
		FileReader();
		FileReader(const char* path);
		~FileReader();

		void OpenFile(const char* path);
		int GetFileSize();

		// Move the file pointer by offset from origin(defaults to current location)
		// see SEEK_SET, SEEK_CUR and SEEK_END
		bool FileSeek(int offset, int origin = SEEK_CUR);

		// Read a 'size' long block of data from file to buffer
		// Buffer is a pointer to the first element of an array
		// Also sets the file pointer to the end of read block
		bool ReadBytes(unsigned int size, void* buffer);

		// Read whole file
		void* ReadBinary();
		const char* ReadText();

	private:
		FILE* file;
	};
}

#endif