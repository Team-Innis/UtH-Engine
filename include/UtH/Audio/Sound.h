#pragma once
#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <AL\al.h>
#include <AL\alc.h>

#include <vector>
#include <UtH\Platform\FileReader.h>
#include <UtH\Math\Vector3.hpp>

namespace uth
{
	class Sound
	{
	public:
		Sound();
		~Sound();

		static Sound* Load(const char* fileName);
		void Play();
		void Play(float offset);
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
		Sound(const Sound&);
		Sound(const char* fileName);

		void Initialize(const char* fileName);
		static void CreateSources(ALuint &source);
		ALint Status();
		void Copy();

		ALuint source;
		ALuint buffer;
		float* data;

		bool loop;
		float duration;
		std::vector<ALuint> tempSource;
		float _posX, _posY, _posZ;
	};
}

#endif