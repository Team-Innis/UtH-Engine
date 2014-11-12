#pragma once
#ifndef TEXTURE_H_UTH
#define TEXTURE_H_UTH

#include <UtH/Platform/Uncopyable.hpp>
#include <pmath/Vector2.hpp>
#include <string>
#include <unordered_map>
#include <memory>


namespace uth
{
    class Texture : private uth::Uncopyable
    {
    private:

        struct Deleter
        {
            void operator()(Texture* file) const
            {
                delete file;
            }
        };


        friend class RenderTexture;
        friend class ResourceManager;

    public:

        void Bind() const;

        static void Unbind();

        bool SetSmooth(const bool value);

        bool SetRepeated(const bool value);

        const pmath::Vec2& GetSize() const;

        bool IsValid() const;

        bool IsSmooth() const;

        bool IsRepeated() const;




    private:

        // Only friend classes can construct a texture.
        Texture();

        ~Texture();

        // These functions are only used by ResourceManager and RenderTexture.
        bool Create(const pmath::Vec2& size, const bool smooth = false, const bool repeated = false);

        bool LoadFromFile(const std::string& filePath, const bool smooth = false, const bool repeated = false);


        
        // Member data

        unsigned int m_textureID;
        pmath::Vec2 m_size;
        bool m_smooth, m_repeated;

    };
}

#endif
