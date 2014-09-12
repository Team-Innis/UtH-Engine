#include <UtH/Resources/SoundBuffer.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/FileReader.hpp>

#include <sndfile/sndfile.h>

namespace uth
{
    SoundBuffer::SoundBuffer()
    {

    }

    SoundBuffer::~SoundBuffer()
    {

    }

    bool SoundBuffer::LoadFromFile(const std::string& filePath)
    {
		SF_INFO soundInfo;

#if defined(UTH_SYSTEM_ANDROID)
		AAsset* asset = FileReader::loadSound(filePath);

		SF_VIRTUAL_IO virtualIO;
		virtualIO.get_filelen = &FileReader::getAssetLength;
		virtualIO.seek = &FileReader::seekAsset;
		virtualIO.read = &FileReader::readAsset;
		virtualIO.tell = &FileReader::tellAsset;	

		SNDFILE* file = sf_open_virtual(&virtualIO, SFM_READ, &soundInfo, asset);
#elif defined(UTH_SYSTEM_WINDOWS)
		SNDFILE* file = sf_open(("assets/" + filePath).c_str(), SFM_READ, &soundInfo);
#endif

		if (!file)
		{
			int error = sf_error(file);
			WriteError("Failed to open sound file, error &d", file, error);
			WriteError(sf_error_number(error));
		}

		WriteLog("Frames: %d\n"		, soundInfo.frames);
		WriteLog("Samplerae: %d\n"	, soundInfo.samplerate);
		WriteLog("Channels: %d\n"	, soundInfo.channels);
		WriteLog("Format: %d\n"		, soundInfo.format);


		m_soundInfo.frames			= static_cast<int>(soundInfo.frames * soundInfo.channels);
		m_soundInfo.channels		= soundInfo.channels;
		m_soundInfo.sampleRate		= soundInfo.samplerate;

		m_soundInfo.soundBuffer = new short[m_soundInfo.frames];
		sf_read_short(file, m_soundInfo.soundBuffer, m_soundInfo.frames);

		sf_close(file);

		return true;	
    }

    const SoundBuffer::SoundStruct& SoundBuffer::GetSoundInfo() const
    {
        return m_soundInfo;
    }

}