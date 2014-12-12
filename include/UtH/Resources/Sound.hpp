#pragma once
#ifndef SOUND_H_UTH
#define SOUND_H_UTH

#include <string>
#include <AL/al.h>
#include <AL/alc.h>

#include <vector>
#include <pmath/Vector3.hpp>
#include <UtH/Resources/Resource.hpp>

namespace uth
{
	class Sound : public Resource
	{
		struct Deleter
		{
			void operator()(Sound* sound)
			{
				delete sound;
			}
		};

		friend class ResourceManager;

		Sound();
		~Sound();

	public:

		// Loads and creates new sound
		//static Sound* Load(std::string fileName);

		// Plays source
		void Play();

		// Plays from specific second
		void Play(float offset);

		// Indented for soundeffects.
		// This function copies sound source and starts
		// to play new source.
		void PlayEffect();

		// Stops source from playing.
		void Stop();

		// Pauses source. Use Play() to continue.
		void Pause();
		void Pause(bool pause);

		// Toggles loop on or off
		void Loop();

		// Sets loop true or false
		void Loop(bool looping);

		// Adjust source volume
		// Use SetListenerVolume if you want copied sounds
		// to use same volume as old one.
		void SetVolume(int volumePercent);

		// Adjust listener volume
		void SetListenerVolume(int volumePercent);

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

		// Check if source is playing.
		bool IsPlaying();

		// Stops all effects
		void StopEffects();

	private:
		Sound(const Sound&);

		bool LoadFromFile(const std::string& filePath) override;
		void Unload() override;
		bool EnsureLoaded() override;

		void Initialize(std::string fileName);
		static void CreateSources(ALuint &source);
		ALint Status();
		void effectCopy();

		ALuint source;
		ALuint buffer;

		bool loop;
		bool enginePaused;
		float duration;
		std::vector<ALuint> tempSource;

		Sound* copy;
		Sound* Copy();
		
		float _posX, _posY, _posZ;

	};
}

#endif