#pragma once
#ifndef SOUNDBUFFER_H_UTH
#define SOUNDBUFFER_H_UTH

#include <UtH/Platform/Typedefs.hpp>
#include <string>

namespace uth
{

    class SoundBuffer
    {
        struct SoundStruct
        {
            char *soundBuffer;
			short bitsPerSample;
			short channels;
			int frames;
			DWORD sampleRate;

            ~SoundStruct()
            {
                delete[] soundBuffer;
            }

        } m_soundInfo;

    public:

        SoundBuffer();

        SoundBuffer(const std::string& filePath);

        ~SoundBuffer();


        bool LoadFromFile(const std::string& filePath);


        const SoundStruct& GetSoundInfo() const;

    };
}

#endif