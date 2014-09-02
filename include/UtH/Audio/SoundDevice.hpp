#pragma once
#ifndef SoundDevice_H
#define SoundDevice_H

#include <AL/al.h>
#include <AL/alc.h>

namespace uth
{
	class SoundDevice
	{
	public:
		SoundDevice();
		~SoundDevice();

	private:
		SoundDevice(const SoundDevice&);

		static ALCdevice* device;
		static ALCcontext* context;
		
		static bool initialized;

		static void CreateContext();
	};
}

#endif