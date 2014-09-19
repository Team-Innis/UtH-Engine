/***
 * Android Specific filereader
 **/
#ifndef FILEREADER_H
#define FILEREADER_H

#include <cstdio>
#include <string>
#include <fstream>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <UtH/Platform/BinaryData.hpp>

namespace uth
{
	class FileManager
	{
	public:
		FileManager();
		FileManager(const std::string& path);
		~FileManager();

		void OpenFile(const std::string& path);
		void CloseFile();
		int GetFileSize();
		
		// Move the file pointer by offset from origin(defaults to beginning of file)
		// see SEEK_SET, SEEK_CUR and SEEK_END
		bool FileSeek(int offset, int origin = SEEK_SET);

		// Read a 'count' ammount of 'blockSize' sized blocks of data from file to buffer
		// Buffer is a pointer to the first element of an array
		// Also sets the file pointer to the end of read block
		bool ReadBytes(void* buffer, unsigned int count, unsigned int blockSize = 1);
		
		// Returns the content of whole file as binary data
		const BINARY_DATA ReadBinary();

		// Returns the content of the whole file as text
		const std::string ReadText();

		// Saves text to file.
		// [PC] Relative to executable location.
		// [Android] Relative to private application data folder.
		void WriteToFile(const std::string& filenameAndPath, const std::string& data,
			bool toSDcard = false);
		// [PC] Relative to executable location.
		// [Android] Relative to private application data folder.
		void WriteToFile(const std::string& filenameAndPath, const BINARY_DATA& data);

		static AAssetManager* m_manager;
		
		
		static AAsset* loadSound(const std::string& fileName);

		static int64_t getAssetLength(void* asset);
		static int64_t seekAsset(int64_t offset, int whence, void* asset);
		static int64_t readAsset(void* buffer, int64_t count, void* asset);
		static int64_t tellAsset(void* asset);
		
	private:
		//std::FILE* m_file;
		std::fstream m_stream;
		AAsset* m_asset;
		unsigned int m_length;
	};
}

#endif