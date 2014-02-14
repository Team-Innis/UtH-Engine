#include <UtH\Audio\Audio.h>

using namespace uth;

Audio::Audio()
{
	_manager = new SoundManager();
}

Audio::~Audio()
{
	delete _sound;
	delete _manager;
}

// Public

// Loads file into source.
void Audio::Load(const char* fileName)
{
	_sound = Sound::Load(fileName);
}
// Plays source.
void Audio::Play()
{
	_sound->Play();
}
// Plays from specific second.
void Audio::Play(float offsetInMilliseconds)
{
	float offset = offsetInMilliseconds / 1000.0f;
	_sound->Play(offset);
}
// Play() funktion for soundeffects.
void Audio::PlayEffect()
{
	_sound->PlayEffect();
}
// Stops playing source.
void Audio::Stop()
{
	_sound->Stop();
}
// Toggles loop on / off.
void Audio::Loop()
{
	_sound->Loop();
}
// Sets loop to desired value.
void Audio::Loop(bool looping)
{
	_sound->Loop(looping);
}
// Adjust volume.
void Audio::SetVolume(int volumePercent)
{
	_sound->SetVolume(volumePercent);
}
// Adjust pitch.
void Audio::SetPitch(int pitchPercent)
{
	_sound->SetPitch(pitchPercent);
}
// Change audiosource position.
void Audio::SetSourcePosition(float x, float y, float z)
{
	_sound->SetSourcePosition(x, y, z);
}

void Audio::SetSourcePosition(umath::vector3 position)
{
	_sound->SetSourcePosition(position);
}
// Change listener position.
void Audio::SetListenerPosition(float x, float y, float z)
{
	_sound->SetListenerPosition(x, y, z);
}

void Audio::SetListenerPosition(umath::vector3 position)
{
	_sound->SetListenerPosition(position);
}