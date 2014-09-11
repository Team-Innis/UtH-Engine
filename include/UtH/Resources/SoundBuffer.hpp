#pragma once
#ifndef SOUNDBUFFER_H_UTH
#define SOUNDBUFFER_H_UTH

#include <UtH/Platform/Typedefs.hpp>
#include <string>

namespace uth
{

    class SoundBuffer
    {
    private:

        struct Deleter
        {
            void operator()(SoundBuffer* file) const
            {
                delete file;
            }
        };

        friend class ResourceManager;

        struct SoundStruct
        {
            short *soundBuffer;
			int channels;
			int frames;
			DWORD sampleRate;

            ~SoundStruct()
            {
                delete[] soundBuffer;
            }

        } m_soundInfo;

    private:

        SoundBuffer();

        ~SoundBuffer();

        bool LoadFromFile(const std::string& filePath);


    public:

        const SoundStruct& GetSoundInfo() const;
    };
}

#endif