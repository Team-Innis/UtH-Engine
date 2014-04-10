#include <UtH/Resources/SoundBuffer.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/FileReader.h>



namespace uth
{
    SoundBuffer::SoundBuffer()
    {

    }

    SoundBuffer::SoundBuffer(const std::string& filePath)
    {
        LoadFromFile(filePath);
    }

    SoundBuffer::~SoundBuffer()
    {

    }



    bool SoundBuffer::LoadFromFile(const std::string& filePath)
    {
        FileReader FR(filePath.c_str());

		BYTE id[4]; // four bytes to hold 'RIFF'
		DWORD size;
		short format_tag, block_align;
		DWORD format_lenght, avg_bytes_sec;
		DWORD data_size, i = 0;

		FR.ReadBytes(id, 4);
		if((char)id[0] == 'R' && (char)id[1] == 'I' && (char)id[2] == 'F' && (char)id[3] == 'F')
		{
			//FR->FileSeek(4, 0);
			FR.ReadBytes(&size, 4);
			WriteLog("Size: %u\n", size);
			//FR->FileSeek(8, 0);
			FR.ReadBytes(id, 4);
			if((char)id[0] == 'W' && (char)id[1] == 'A' && (char)id[2] == 'V' && (char)id[3] == 'E')
			{
				//FR->FileSeek(12, 0);
				FR.ReadBytes(id, 4);
				WriteLog((char*)id);
				//FR->FileSeek(16, 0);
				FR.ReadBytes(&format_lenght, 4);
				i += format_lenght;
				WriteLog("\nBlock lenght: %lu\n", format_lenght);
				//FR->FileSeek(20, 0);
				FR.ReadBytes(&format_tag, 2);
				WriteLog("Format tag: %d\n", format_tag);
				if(format_tag != 1)
				{
					WriteError("Only PCM format supported!");
					return false;
				}
				//FR->FileSeek(22, 0);
				FR.ReadBytes(&m_soundInfo.channels, 2);
				WriteLog("Channels: %d\n", m_soundInfo.channels);
				//FR->FileSeek(24, 0);
				FR.ReadBytes(&m_soundInfo.sampleRate, 4);
				WriteLog("Sample rate: %lu\n", m_soundInfo.sampleRate);
				//FR->FileSeek(28, 0);
				FR.ReadBytes(&avg_bytes_sec, 4);
				WriteLog("Avg bytes sec: %lu\n", avg_bytes_sec);
				//FR->FileSeek(32, 0);
				FR.ReadBytes(&block_align, 2);
				WriteLog("Block align: %d\n", block_align);
				//FR->FileSeek(34, 0);
				FR.ReadBytes(&m_soundInfo.bitsPerSample, 2);
				WriteLog("Bits per sample: %d\n", m_soundInfo.bitsPerSample);
				//FR->FileSeek(20 + i, 0);

				if(m_soundInfo.channels == 1 && m_soundInfo.bitsPerSample == 8)
				{
					WriteError("For some reason 8bit MONO doesnt work!"
								"\nSo it's not supported.");
					return false;
				}
				FR.ReadBytes(id, 4);
				WriteLog((char*)id);
				if((char)id[0] != 'd' || (char)id[1] != 'a' || (char)id[2] != 't' || (char)id[3] != 'a')
				{
					FR.FileSeek(20 + i, 0);
					//FR.ReadBytes(&format_lenght, 4);
					//i += format_lenght;
					//WriteLog("\nBlock lenght: %lu\n", format_lenght);
					//FR.FileSeek(28 + i, 0);
					FR.ReadBytes(id, 4);
					WriteLog((char*)id);
				}
				//FR->FileSeek(32 + i, 0);
				FR.ReadBytes(&data_size, 4);
				WriteLog("\nData size %lu\n", data_size);
				m_soundInfo.soundBuffer = new short[data_size];
				//FR->FileSeek(36 + i, 0);
				FR.ReadBytes(m_soundInfo.soundBuffer, data_size);
				WriteLog("Sound buffer: %u\n", m_soundInfo.soundBuffer);
			}
			else
			{
				WriteError("Not a WAVE file!");
				return false;
			}
		}
		else
		{
			WriteError("Not a RIFF file!");
			return false;
		}

		m_soundInfo.frames = data_size / block_align;
		WriteLog("Frames: %d\n", m_soundInfo.frames);

        return true;
    }


    const SoundBuffer::SoundStruct& SoundBuffer::GetSoundInfo() const
    {
        return m_soundInfo;
    }

}