#include <UtH\Resources\ResourceManager.h>

using namespace uth;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}


void ResourceManager::loadWAV(const char* filePath)
{
	bool newSoundFile = true;

	if(!s_Info.empty())
	{
		std::map<const char*, SoundInfo>::iterator it;
		for(it = s_Info.begin(); it != s_Info.end(); it++)
		{
			if(it->first == filePath)
			{
				newSoundFile = false;

				soundInfo.bitsPerSample =	(*it).second.bitsPerSample;
				soundInfo.channels =		(*it).second.channels;
				soundInfo.channels =		(*it).second.frames;
				soundInfo.sampleRate =		(*it).second.sampleRate;
				soundInfo.soundBuffer =		(*it).second.soundBuffer;
				break;
			}
		}	
	}
	else if(newSoundFile)
	{
		FileReader* FR = new FileReader(filePath);

		BYTE id[4]; // four bytes to hold 'RIFF'
		short *sound_buffer;
		DWORD size;
		short format_tag, channels, block_align, bits_per_sample;
		DWORD format_lenght, sample_rate, avg_bytes_sec;
		DWORD data_size, i = 0;

		FR->ReadBytes(id, 4);
		if((char)id[0] == 'R' && (char)id[1] == 'I' && (char)id[2] == 'F' && (char)id[3] == 'F')
		{
			//FR->FileSeek(4, 0);
			FR->ReadBytes(&size, 4);
			WriteLog("Size: %u\n", size);
			//FR->FileSeek(8, 0);
			FR->ReadBytes(id, 4);
			if((char)id[0] == 'W' && (char)id[1] == 'A' && (char)id[2] == 'V' && (char)id[3] == 'E')
			{
				//FR->FileSeek(12, 0);
				FR->ReadBytes(id, 4);
				WriteLog((char*)id);
				//FR->FileSeek(16, 0);
				FR->ReadBytes(&format_lenght, 4);
				i += format_lenght;
				WriteLog("\nBlock lenght: %lu\n", format_lenght);
				//FR->FileSeek(20, 0);
				FR->ReadBytes(&format_tag, 2);
				WriteLog("Format tag: %d\n", format_tag);
				if(format_tag != 1)
				{
					WriteLog("Only PCM format supported!\n");
					return;
				}
				//FR->FileSeek(22, 0);
				FR->ReadBytes(&channels, 2);
				WriteLog("Channels: %d\n", channels);
				//FR->FileSeek(24, 0);
				FR->ReadBytes(&sample_rate, 4);
				WriteLog("Sample rate: %lu\n");
				//FR->FileSeek(28, 0);
				FR->ReadBytes(&avg_bytes_sec, 4);
				WriteLog("Avg bytes sec: %lu\n", avg_bytes_sec);
				//FR->FileSeek(32, 0);
				FR->ReadBytes(&block_align, 2);
				WriteLog("Block align: %d\n", block_align);
				//FR->FileSeek(34, 0);
				FR->ReadBytes(&bits_per_sample, 2);
				WriteLog("Bits per sample: %d\n", bits_per_sample);
				//FR->FileSeek(20 + i, 0);

				FR->ReadBytes(id, 4);
				WriteLog((char*)id);
				if((char)id[0] != 'd' && (char)id[1] != 'a' && (char)id[2] != 't' && (char)id[3] != 'a')
				{
					FR->FileSeek(24 + i, 0);
					FR->ReadBytes(&format_lenght, 4);
					i += format_lenght;
					WriteLog("\nBlock lenght: %lu\n", format_lenght);
					FR->FileSeek(28 + i, 0);
					FR->ReadBytes(id, 4);
					WriteLog((char*)id);
				}
				//FR->FileSeek(32 + i, 0);
				FR->ReadBytes(&data_size, 4);
				WriteLog("\nData size %lu\n", data_size);
				sound_buffer = (short *)malloc(sizeof(short) * data_size);
				//FR->FileSeek(36 + i, 0);
				FR->ReadBytes(sound_buffer, data_size);
				WriteLog("Sound buffer: %u\n", sound_buffer);
			}
			else
				WriteLog("Not a WAVE file!\n");
		}
		else
			WriteLog("Not a RIFF file!\n");
	

		int frames = data_size / block_align;
		WriteLog("Frames: %d\n", frames);

		soundInfo.channels = channels;
		soundInfo.frames = frames;
		soundInfo.sampleRate = sample_rate;
		soundInfo.soundBuffer = sound_buffer;
		soundInfo.bitsPerSample = bits_per_sample;

		delete FR;
		s_Info.insert(std::make_pair(filePath, soundInfo));
	}
}

void ResourceManager::loadTGA(const char* filePath)
{
	bool newTextureFile = true;

	if(!_header.empty())
	{
		std::map<const char*, Header>::iterator it;
		for(it = _header.begin(); it != _header.end(); it++)
		{
			if(it->first == filePath)
			{
				newTextureFile = false;

				header.depth = (*it).second.depth;
				header.descriptor = (*it).second.descriptor;
				header.height = (*it).second.height;
				header.pixels = (*it).second.pixels;
				header.type = (*it).second.type;
				header.width = (*it).second.width;
				break;
			}
		}
	}

	else if(newTextureFile)
	{
		FileReader* FR = new FileReader(filePath);
		BYTE* buffer = (BYTE*)malloc(sizeof(BYTE)*1);

		//header
		FR->FileSeek(2, 0);
		FR->ReadBytes(buffer, 1);
		header.type = buffer[0];
		assert((int)header.type == 2);
		free(buffer);

		buffer = (BYTE*)malloc(sizeof(BYTE)*4);
		FR->FileSeek(12, 0);
		FR->ReadBytes(buffer, 4);
		header.width = buffer[0] + buffer[1] * 256;
		header.height = buffer[2] + buffer[3] * 256;
		free(buffer);

		//bpp
		buffer = (BYTE*)malloc(sizeof(BYTE)*1);
		FR->FileSeek(16, 0);
		FR->ReadBytes(buffer, 1);
		header.depth = buffer[0];
		assert(header.depth == 24 || header.depth == 32);
		free(buffer);

		//data
		int datasize = header.width * header.height * header.depth/8;
		header.pixels = (BYTE*)(malloc(sizeof(BYTE)*datasize));
		buffer = (BYTE*)malloc(sizeof(BYTE)*datasize);
		FR->FileSeek(18, 0);
		FR->ReadBytes(buffer, datasize);

		//(pixels) rgb = bgr(tga)
		for(int i = 0; i < datasize; i+=4)
		{
			header.pixels[i+0] = buffer[i+2];
			header.pixels[i+1] = buffer[i+1];
			header.pixels[i+2] = buffer[i+0];
			header.pixels[i+3] = buffer[i+3];
		}
		free(buffer);
		delete FR;

		_header.insert(std::make_pair(filePath, header));
	}
}