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

		bool LoadFromFile(const std::string& filePath) override;
		void Unload() override;
		void Initialize(std::string fileName);
		static void CreateSources(ALuint &source);
		ALint Status();
		void Copy();

		//void InsertToMap(std::string fileName);
		//void RemoveFromMap(std::string fileName);

		ALuint source;
		ALuint buffer;

		bool loop;
		float duration;
		std::vector<ALuint> tempSource;
		float _posX, _posY, _posZ;

	};
}

#endif