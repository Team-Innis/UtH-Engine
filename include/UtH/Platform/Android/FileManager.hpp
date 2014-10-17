/***
 * Android Specific filereader
 **/
#ifndef FILEREADER_H
#define FILEREADER_H

#include <cstdio>
#include <string>
#include <fstream>
#include <UtH/Platform/BinaryData.hpp>

struct AAssetManager;
struct AAsset;

namespace uth
{
	class FileManager
	{
	public:
		enum class Location
		{
			ASSET = 0,
			EXTERNAL = 1,
			INTERNAL = 2,
		};

		FileManager();
		FileManager(const std::string& path, const Location = Location::ASSET,
            bool WriteToFile = false);
		~FileManager();

		void OpenFile(const std::string& path, const Location = Location::ASSET,
            bool WriteToFile = false);
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
		// Location::INTERNAL path:
		//		@android: "/data/data/net.app.name/" (hidden file)
		//		@pc:	  "/internal/"
		// Location::EXTERNAL:
		//		@android: "/sdcard/"
		//		@pc:	  "/external/"
		// Location::ASSET: not available
		void WriteString(const std::string& data);

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
        bool m_writable;
	};
}

#endif