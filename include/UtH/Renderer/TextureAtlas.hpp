#pragma once
#ifndef TEXTUREATLAS_H_UTH
#define TEXTUREATLAS_H_UTH

#include <UtH/Renderer/Texture.hpp>
#include <UtH/Math/Rectangle.hpp>
#include <map>


namespace uth
{
    class TextureAtlas : private Uncopyable
    {
    public:

        TextureAtlas();

        TextureAtlas(const std::string& path);

        ~TextureAtlas();


        bool LoadFromFile(const std::string& filePath);

        void Bind();

        unsigned int GetTextureID() const;

        bool SetSmooth(const bool value);

        const umath::vector2& GetSize() const;

        bool IsValid() const;

        bool IsSmooth() const;

        const umath::rectangle& getTextureCoords(const char* name) const;


    private:

        Texture* m_texture;
        std::map<std::string, umath::rectangle> m_textureRects;
    };
}

#endif