#pragma once
#ifndef SOUND_H_UTH
#define SOUND_H_UTH

#include <string>
#include <AL/al.h>
#include <AL/alc.h>

#include <vector>
#include <UtH/Platform/FileManager.hpp>
#include <pmath/Vector3.hpp>

namespace uth
{
	class Sound
	{
	public:
		Sound();
		~Sound();

		// Loads and creates new sound
		static Sound* Load(const char* fileName);

		// Plays source
		void Play();

		// Plays from specific second
		void Play(float offset);

		// Intented for soundeffects.
		// This function copies sound source and starts
		// to play new source.
		void PlayEffect();

		// Stops source from playing.
		void Stop();

		// Toggles between playing and paused.
		void Pause();

		// Toggles loop on or off
		void Loop();

		// Sets loop true or false
		void Loop(bool looping);

		// Adjust volume
		void SetVolume(int volumePercent);

		// Adjust pitch
		void SetPitch(int pitchPercent);
		
		// Adjust source position
		void SetSourcePosition(float x, float y, float z = 0);
		// Adjust source position
		void SetSourcePosition(pmath::Vec3 position);

		// Adjust listener position
		void SetListenerPosition(float x, float y, float z = 0);
		// Adjust listener position
		void SetListenerPosition(pmath::Vec3 position);

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