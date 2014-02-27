// This class is for sound wrapping.

#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <UtH\Audio\Sound.h>
#include <UtH\Audio\SoundManager.h>

namespace uth
{
	class Audio
	{
	public:
		Audio();
		~Audio();

		void Load(const char* fileName);
		void Play();
		void Play(float offsetInMilliseconds);
		void PlayEffect();
		void Stop();
		void Pause();

		void Loop();
		void Loop(bool looping);
		void SetVolume(int volumePercent);
		void SetPitch(int pitchPercent);
		
		void SetSourcePosition(float x, float y, float z = 0);
		void SetSourcePosition(umath::vector3 position);

		void SetListenerPosition(float x, float y, float z = 0);
		void SetListenerPosition(umath::vector3 position);

	private:
		Sound* _sound;
		SoundManager* _manager;
	};
}

#endif