#include <UtH/Audio/Sound.hpp>
#include <UtH/Platform/Typedefs.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Resources/ResourceManager.h>

using namespace uth;


Sound::Sound()
{
}

Sound::~Sound()
{
	alDeleteSources(1, &source);
	alDeleteBuffers(1, &buffer);

	for(size_t i = 0; i < tempSource.size(); i++)
	{
		alDeleteSources(1, &tempSource[i]);
	}
}

Sound::Sound(const char* fileName)
	: loop(false),
	  duration(0.1f),
	  _posX(0), _posY(0), _posZ(0)
{
	Initialize(fileName);
}

// PUBLIC
Sound* Sound::Load(const char* fileName)
{
	return new Sound(fileName);
}
// Plays source
void Sound::Play()
{
	alSourcePlay(source);
}
// Plays from specific second
void Sound::Play(float offset)
{
	if(offset >= duration)
		WriteError("Offset %f exceeds %f duration!", offset, duration);
	else
	{
		alSourcei(source, AL_SEC_OFFSET, static_cast<ALint>(offset));
		alSourcePlay(source);
	}
}
// Intented for soundeffects.
// This function copies sound source and starts
// to play new source.
void Sound::PlayEffect()
{
	if(Status() != AL_PLAYING)
		alSourcePlay(source);
	else
		Copy();
}
// Stops source from playing.
void Sound::Stop()
{
	alSourceStop(source);
}
// Toggles between playing and paused.
void Sound::Pause()
{
	if(Status() == AL_PLAYING)
		alSourcePause(source);
	else
		alSourcePlay(source);
}
// Toggles loop on or off
void Sound::Loop()
{
	if(loop)
	{
		alSourcei(source, AL_LOOPING, AL_FALSE);
		loop = false;
	}
	else if(!loop)
	{
		alSourcei(source, AL_LOOPING, AL_TRUE);
		loop = true;
	}
}
// Sets loop true or false
void Sound::Loop(bool looping)
{
	if(looping == 0)
		loop = false;
	else
		loop = true;

	alSourcei(source, AL_LOOPING, looping);
	CheckALError("al_sourcei AL_LOOPING");
}
// Adjust volume
void Sound::SetVolume(int volumePercent)
{
	float newVolume = float(volumePercent) / 100.0f;
	alSourcef(source, AL_GAIN, newVolume);
	CheckALError("al_sourcef AL_GAIN");
}
// Adjust pitch
void Sound::SetPitch(int pitchPercent)
{
	float newPitch = float(pitchPercent) / 100.0f;
	alSourcef(source, AL_PITCH, newPitch);
	CheckALError("al_sourcef AL_PITCH");
}
// Adjust source position
void Sound::SetSourcePosition(float x, float y, float z)
{
	_posX = x; _posY = y; _posZ = z;
	alSource3f(source, AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_POSITION");
	alSource3f(source, AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_VELOCITY");
}
void Sound::SetSourcePosition(umath::vector3 position)
{
	_posX = position.x; _posY = position.y; _posZ = position.z;
	alSource3f(source, AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_POSITION");
	alSource3f(source, AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_VELOCITY");
}
// Adjust listener position
void Sound::SetListenerPosition(float x, float y, float z)
{
	_posX = x; _posY = y; _posZ = z;
	alListener3f(AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_slistener3f AL_POSITION");
	alListener3f(AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_listener3f AL_VELOCITY");
}
void Sound::SetListenerPosition(umath::vector3 position)
{
	_posX = position.x; _posY = position.y; _posZ = position.z;
	alListener3f(AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_slistener3f AL_POSITION");
	alListener3f(AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_listener3f AL_VELOCITY");
}

// PRIVATE

void Sound::Initialize(const char* fileName)
{
	const SoundBuffer* buf = uthRS.LoadSoundBuffer(fileName);

	if (!buf)
		return;

	Sound::CreateSources(source);
	// Create buffer
	alGenBuffers(1, &buffer);
	CheckALError("alGenBuffers");

	short channels = buf->GetSoundInfo().channels;
	if(buf->GetSoundInfo().bitsPerSample == 16)
	{
		alBufferData(buffer, channels == 2 ? AL_FORMAT_STEREO16:AL_FORMAT_MONO16 ,
			buf->GetSoundInfo().soundBuffer,
			buf->GetSoundInfo().frames * sizeof(short) * channels,
			buf->GetSoundInfo().sampleRate);
	}
	else if(buf->GetSoundInfo().bitsPerSample == 8)
	{
		alBufferData(buffer, channels == 2 ? AL_FORMAT_STEREO8:AL_FORMAT_MONO8,
			buf->GetSoundInfo().soundBuffer,
			buf->GetSoundInfo().frames * sizeof(char) * channels,
			buf->GetSoundInfo().sampleRate);
	}
	

	CheckALError("alBufferData");

	alSourcei(source, AL_BUFFER, buffer);
	CheckALError("alSourcei");

	duration = static_cast<float>(buf->GetSoundInfo().frames) / static_cast<float>(buf->GetSoundInfo().sampleRate);
	WriteLog("duration: %f\n", duration);
}

void Sound::CreateSources(ALuint &source)
{
	// create source
	alGenSources(1, &source);
	CheckALError("alGen_sources");
	// set normal pitch = 1
	alSourcef(source, AL_PITCH, 1);
	CheckALError("al_sourcef AL_PITCH");
	// set maximum volume = 1
	alSourcef(source, AL_GAIN, 1);
	CheckALError("al_sourcef AL_GAIN");
	// set position to center
	alSource3f(source, AL_POSITION, 0, 0, 0);
	CheckALError("al_source3f AL_POSITION");
	// set velocity to center
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	CheckALError("al_source3f AL_VELOCITY");
	// default set for loop = false
	alSourcei(source, AL_LOOPING, AL_FALSE);
	CheckALError("al_sourcei AL_LOOPING");
}
// Returns in what state source is currently.
ALint Sound::Status()
{
	ALint _state;
	alGetSourcei(source, AL_SOURCE_STATE, &_state);
	return _state;
}
// Copies effect sound into vector and starts to play it.
// Removes already finished playback from beginning of vector.
void Sound::Copy()
{
	ALuint source;
	Sound::CreateSources(source);
	// We want to put copied sound in same location as copied source.
	alSource3f(source, AL_POSITION, _posX, _posY, _posZ);
	alSource3f(source, AL_VELOCITY, _posX, _posY, _posZ);

	alSourcei(source, AL_BUFFER, buffer);
	CheckALError("alSourcei AL_BUFFER");

	// Push new source into vector.
	tempSource.push_back(source);
	alSourcePlay(tempSource[tempSource.size()-1]);
	// Remove source from beginning of vector as it finishes playback.
	tempSource.erase(tempSource.begin());
}