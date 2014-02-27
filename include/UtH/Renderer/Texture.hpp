#pragma once
#ifndef TEXTURE_H_UTH
#define TEXTURE_H_UTH

#include <UtH\Platform\Uncopyable.hpp>
#include <UtH\Math\Vector2.hpp>



namespace uth
{
    class Texture : private uth::Uncopyable
    {
    public:

        Texture();

        ~Texture();


        /// Only supports uncompressed .tga for now.
        bool LoadFromFile(const char* path, const bool smooth = false, const bool repeated = false);

        void Bind();

        const unsigned int GetTextureID() const;

        bool SetSmooth(const bool value);

        bool SetRepeated(const bool value);

        const umath::vector2& GetSize() const;

        const bool IsValid() const;

        const bool IsSmooth() const;

        const bool IsRepeated() const;




    private:

        unsigned int m_textureID;
        umath::vector2 m_size;
        bool m_smooth, m_repeated;

    };
}

#endif