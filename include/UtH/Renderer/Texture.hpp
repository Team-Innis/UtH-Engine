#pragma once

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
        bool loadFromFile(const char* path, const bool smooth = false, const bool repeated = false);

        void bind();

        const unsigned int getTextureID() const;

        bool setSmooth(const bool value);

        bool setRepeated(const bool value);

        const umath::vector2& getSize() const;

        const bool isValid() const;

        const bool isSmooth() const;

        const bool isRepeated() const;




    private:

        unsigned int m_textureID;
        umath::vector2 m_size;
        bool m_smooth, m_repeated;

    };
}