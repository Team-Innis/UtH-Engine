#pragma once
#ifndef RESOURCEMANAGER_H_UTH
#define RESOURCEMANAGER_H_UTH

#include <UtH\Platform\FileReader.h>
#include <UtH\Platform\Debug.hpp>
#include <UtH\Platform\Singleton.hpp>
#include <UtH\Platform\Typedefs.hpp>

#include <map>
#include <utility>

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
		};
		struct Header
		{
			BYTE* pixels;
			BYTE type;
			USHORT width;
			USHORT height;
			BYTE depth;
			BYTE descriptor;
		};

		SoundInfo soundInfo;
		Header header;

		void loadWAV(const char* filePath);
		void loadTGA(const char* filePath);

	private:
		ResourceManager();
		~ResourceManager();

		std::map<const char*, SoundInfo> s_Info;
		std::map<const char*, Header> _header;
		
	};
}
#endif