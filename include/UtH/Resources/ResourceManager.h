#pragma once
#ifndef RESOURCEMANAGER_H_UTH
#define RESOURCEMANAGER_H_UTH

#include <UtH\Platform\FileReader.h>
#include <UtH\Core\Debug.hpp>
#include <UtH\Platform\Singleton.hpp>

#define uthRS uth::ResourceManager::getInstance()

namespace uth
{
	class ResourceManager : public uth::Singleton<uth::ResourceManager>
	{

		friend class Singleton<uth::ResourceManager>;

	public:
		struct SoundInfo
		{
			short *soundBuffer;
			short bitsPerSample;
			short channels;
			int frames;
			DWORD sampleRate;
		} soundInfo;
		struct Header
		{
			BYTE* pixels;
			BYTE type;
			USHORT width;
			USHORT height;
			BYTE depth;
			BYTE descriptor;
		}header;

		void loadWAV(const char* filePath);
		void loadTGA(const char* filePath);

	private:
		ResourceManager();
		~ResourceManager();
	};
}
#endif