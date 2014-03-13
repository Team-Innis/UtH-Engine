#include <UtH/Audio/SoundManager.h>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

bool SoundManager::initialized = false;
ALCdevice* SoundManager::device = 0;
ALCcontext* SoundManager::context = 0;

SoundManager::SoundManager()
{
	CreateContext();
}

SoundManager::~SoundManager()
{
	alcMakeContextCurrent(0);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

// PRIVATE

void SoundManager::CreateContext()
{
	if(!initialized)
	{
		initialized = true;

		device = alcOpenDevice(0);
		if(!device)
			WriteLog("Failed to open audio device!");

		WriteLog("Audio device opened.\n");

		context = alcCreateContext(device, 0);
		if(!alcMakeContextCurrent(context))
		{
			WriteLog("Failed to make context current!");
			CheckALError("alcMakeContextCurrent");
		}
	}
}