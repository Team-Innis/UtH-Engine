#include <UtH/Platform/SoundDevice.hpp>
#include <UtH/Platform/Debug.hpp>
#include <cassert>

using namespace uth;

//bool SoundDevice::initialized = false;
//ALCdevice* SoundDevice::device = 0;
//ALCcontext* SoundDevice::context = 0;

SoundDevice::SoundDevice()
	: device(0),
	context(0),
    initialized(false)
{
	CreateContext();
}

SoundDevice::~SoundDevice()
{
	alcMakeContextCurrent(0);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

bool SoundDevice::DeviceInitialized()
{
	return initialized;
}

// PRIVATE

void SoundDevice::CreateContext()
{
	if(!initialized)
	{
		device = alcOpenDevice(0);

		if (!device)
		{
			WriteError("Failed to open audio device!");
			//assert(false);
			return;
		}
		else
			WriteLog("Audio device opened.\n");

		context = alcCreateContext(device, 0);
		if(!alcMakeContextCurrent(context))
		{
			WriteError("Failed to make context current!");
			CheckALError("alcMakeContextCurrent");
		}
		initialized = true;
	}
}