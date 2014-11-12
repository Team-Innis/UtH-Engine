#include <UtH/Resources/Sound.hpp>
#include <UtH/Platform/Typedefs.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <UtH/Platform/SoundDevice.hpp>
#include <UtH/Platform/FileManager.hpp>

#include <sndfile/sndfile.h>

using namespace uth;



Sound::Sound()
	: loop(false),
	  duration(0.1f),
	  _posX(0), _posY(0), _posZ(0)
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

// PUBLIC
void Sound::Play()
{
	alSourcePlay(source);
}

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

void Sound::PlayEffect()
{
	if(Status() != AL_PLAYING)
		alSourcePlay(source);
	else
		Copy();
}

void Sound::Stop()
{
	alSourceStop(source);
}

void Sound::Pause()
{
	if(Status() == AL_PLAYING)
		alSourcePause(source);
	//else
	//	alSourcePlay(source);
}

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

void Sound::Loop(bool looping)
{
	if(looping == 0)
		loop = false;
	else
		loop = true;

	alSourcei(source, AL_LOOPING, looping);
	CheckALError("al_sourcei AL_LOOPING");
}

void Sound::SetVolume(int volumePercent)
{
	float newVolume = float(volumePercent) / 100.0f;
	alSourcef(source, AL_GAIN, newVolume);
	CheckALError("al_sourcef AL_GAIN");
}

void Sound::SetPitch(int pitchPercent)
{
	float newPitch = float(pitchPercent) / 100.0f;
	alSourcef(source, AL_PITCH, newPitch);
	CheckALError("al_sourcef AL_PITCH");
}

void Sound::SetSourcePosition(float x, float y, float z)
{
	_posX = x; _posY = y; _posZ = z;
	alSource3f(source, AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_POSITION");
	alSource3f(source, AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_VELOCITY");
}
void Sound::SetSourcePosition(pmath::Vec3 position)
{
	_posX = position.x; _posY = position.y; _posZ = position.z;
	alSource3f(source, AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_POSITION");
	alSource3f(source, AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_source3f AL_VELOCITY");
}

void Sound::SetListenerPosition(float x, float y, float z)
{
	_posX = x; _posY = y; _posZ = z;
	alListener3f(AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_slistener3f AL_POSITION");
	alListener3f(AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_listener3f AL_VELOCITY");
}
void Sound::SetListenerPosition(pmath::Vec3 position)
{
	_posX = position.x; _posY = position.y; _posZ = position.z;
	alListener3f(AL_POSITION, _posX, _posY, _posZ);
	CheckALError("al_slistener3f AL_POSITION");
	alListener3f(AL_VELOCITY, _posX, _posY, _posZ);
	CheckALError("al_listener3f AL_VELOCITY");
}

bool Sound::IsPlaying()
{
	if (Status() == AL_PLAYING)
		return true;
	else
		return false;
}

// PRIVATE
bool Sound::Load(std::string fileName)
{
	Initialize(fileName);

	if (source)
		return true;

	return false;
}

void Sound::Initialize(std::string fileName)
{
	uth::SoundDevice::getInstance();

	SF_INFO soundInfo;

#if defined(UTH_SYSTEM_ANDROID)
	AAsset* asset = FileManager::loadSound(fileName);

	SF_VIRTUAL_IO virtualIO;
	virtualIO.get_filelen = &FileManager::getAssetLength;
	virtualIO.seek = &FileManager::seekAsset;
	virtualIO.read = &FileManager::readAsset;
	virtualIO.tell = &FileManager::tellAsset;

	SNDFILE* file = sf_open_virtual(&virtualIO, SFM_READ, &soundInfo, asset);
#elif defined(UTH_SYSTEM_WINDOWS)
	SNDFILE* file = sf_open(("assets/" + fileName).c_str(), SFM_READ, &soundInfo);
#endif

	if (!file)
	{
		int error = sf_error(file);
		WriteError("Failed to open sound file, error &d", file, error);
		WriteError(sf_error_number(error));
	}

	WriteLog("Frames: %d\n", soundInfo.frames);
	WriteLog("Samplerae: %d\n", soundInfo.samplerate);
	WriteLog("Channels: %d\n", soundInfo.channels);
	WriteLog("Format: %d\n", soundInfo.format);


	int frames = static_cast<int>(soundInfo.frames * soundInfo.channels);
	int channels = soundInfo.channels;
	int sampleRate = soundInfo.samplerate;

	short* soundBuffer = new short[frames];
	sf_read_short(file, soundBuffer, frames);

	sf_close(file);


	Sound::CreateSources(source);
	// Create buffer
	alGenBuffers(1, &buffer);
	CheckALError("alGenBuffers");

	//int channels = buf->GetSoundInfo().channels;

	alBufferData(buffer, channels == 2 ? AL_FORMAT_STEREO16:AL_FORMAT_MONO16 ,
		soundBuffer,
		frames * sizeof(short),
		sampleRate);

	CheckALError("alBufferData");

	alSourcei(source, AL_BUFFER, buffer);
	CheckALError("alSourcei");

	duration = static_cast<float>(frames)
		/ static_cast<float>(sampleRate)
		/ static_cast<float>(channels);
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