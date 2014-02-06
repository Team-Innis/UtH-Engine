#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <AL\al.h>
#include <AL\alc.h>

namespace uth
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

	private:
		SoundManager(const SoundManager&);

		static ALCdevice* device;
		static ALCcontext* context;
		
		static bool initialized;

		static void CreateContext();
	};
}

#endif