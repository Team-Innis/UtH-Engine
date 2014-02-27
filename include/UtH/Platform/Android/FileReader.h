/***
 * Android Specific filereader
 **/
#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

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

		// Read a 'count' ammount of 'blockSize' sized blocks of data from file to buffer
		// Buffer is a pointer to the first element of an array
		// Also sets the file pointer to the end of read block
		bool ReadBytes(void* buffer, unsigned int count, unsigned int blockSize = 1);

		// Read whole file
		void* ReadBinary();
		const char* ReadText();

		static AAssetManager* m_manager;
	private:
		//FILE* file;
		AAsset* m_asset;
		unsigned int m_length;
	};
}

#endif