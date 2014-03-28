#pragma once
#ifndef TEXTURE_H_UTH
#define TEXTURE_H_UTH

#include <UtH/Platform/Uncopyable.hpp>
#include <UtH/Math/Vector2.hpp>
#include <string>



namespace uth
{
    class Texture : private uth::Uncopyable
    {
    public:

        Texture();

        Texture(const std::string& filePath);

        ~Texture();


        bool Create(const umath::vector2& size, const bool smooth = false, const bool repeated = false);

        /// Only supports uncompressed .tga for now.
        bool LoadFromFile(const std::string& filePath, const bool smooth = false, const bool repeated = false);

        void Bind() const;

        static void Unbind();

        unsigned int GetTextureID() const;

        bool SetSmooth(const bool value);

        bool SetRepeated(const bool value);

        const umath::vector2& GetSize() const;

        bool IsValid() const;

        bool IsSmooth() const;

        bool IsRepeated() const;




    private:

        unsigned int m_textureID;
        umath::vector2 m_size;
        bool m_smooth, m_repeated;

    };
}

#endif
