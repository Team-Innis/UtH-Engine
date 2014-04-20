#include <UtH/Audio/SoundDevice.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

bool SoundDevice::initialized = false;
ALCdevice* SoundDevice::device = 0;
ALCcontext* SoundDevice::context = 0;

SoundDevice::SoundDevice()
{
	CreateContext();
}

SoundDevice::~SoundDevice()
{
	alcMakeContextCurrent(0);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

// PRIVATE

void SoundDevice::CreateContext()
{
	if(!initialized)
	{
		initialized = true;

		device = alcOpenDevice(0);

		if(!device)
			WriteError("Failed to open audio device!");
		else
			WriteLog("Audio device opened.\n");

		context = alcCreateContext(device, 0);
		if(!alcMakeContextCurrent(context))
		{
			WriteError("Failed to make context current!");
			CheckALError("alcMakeContextCurrent");
		}
	}
}