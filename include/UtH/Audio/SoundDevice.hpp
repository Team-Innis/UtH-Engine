#pragma once
#ifndef SoundDevice_H
#define SoundDevice_H

#include <AL/al.h>
#include <AL/alc.h>

#include <UtH/Platform/Singleton.hpp>

namespace uth
{
	class SoundDevice : public Singleton<SoundDevice>
	{
		friend class Singleton < SoundDevice > ;
	public:
		SoundDevice();
		~SoundDevice();

	private:
		SoundDevice(const SoundDevice&);

		 ALCdevice* device;
		 ALCcontext* context;
		
		 bool initialized;

		 void CreateContext();
	};
}

#endif