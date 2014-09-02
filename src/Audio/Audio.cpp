#include <UtH/Audio/Audio.hpp>

using namespace uth;

Audio::Audio()
{
}

Audio::~Audio()
{
	delete m_sound;
}

// Public

// Loads file into source.
void Audio::Load(const char* fileName)
{
	m_sound = Sound::Load(fileName);
}
// Plays source.
void Audio::Play()
{
	m_sound->Play();
}
// Plays from specific second.
void Audio::Play(float offsetInMilliseconds)
{
	float offset = offsetInMilliseconds / 1000.0f;
	m_sound->Play(offset);
}
// Play() funktion for soundeffects.
void Audio::PlayEffect()
{
	m_sound->PlayEffect();
}
// Stops playing source.
void Audio::Stop()
{
	m_sound->Stop();
}
// Toggles loop on / off.
void Audio::Loop()
{
	m_sound->Loop();
}
// Sets loop to desired value.
void Audio::Loop(bool looping)
{
	m_sound->Loop(looping);
}
// Adjust volume.
void Audio::SetVolume(int volumePercent)
{
	m_sound->SetVolume(volumePercent);
}
// Adjust pitch.
void Audio::SetPitch(int pitchPercent)
{
	m_sound->SetPitch(pitchPercent);
}
// Change audiosource position.
void Audio::SetSourcePosition(float x, float y, float z)
{
	m_sound->SetSourcePosition(x, y, z);
}

void Audio::SetSourcePosition(umath::vector3 position)
{
	m_sound->SetSourcePosition(position);
}
// Change listener position.
void Audio::SetListenerPosition(float x, float y, float z)
{
	m_sound->SetListenerPosition(x, y, z);
}

void Audio::SetListenerPosition(umath::vector3 position)
{
	m_sound->SetListenerPosition(position);
}