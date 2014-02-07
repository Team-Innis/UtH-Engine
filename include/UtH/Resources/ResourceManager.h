#pragma once
#ifndef RESOURCEMANAGER_H_UTH
#define RESOURCEMANAGER_H_UTH

#include <UtH\Platform\FileReader.h>
#include <UtH\Core\Debug.hpp>

namespace uth
{
	class ResourceManager
	{
	public:
		struct SoundInfo
		{
			short *soundBuffer;
			short bitsPerSample;
			short channels;
			int frames;
			DWORD sampleRate;
		} soundInfo;

		ResourceManager();
		~ResourceManager();

		void loadWAV(const char* filePath);
		void loadTGA(const char* filePath);

	private:
		ResourceManager(const ResourceManager&);
	};
}
#endif