#pragma once
#ifndef RESOURCEMANAGER_H_UTH
#define RESOURCEMANAGER_H_UTH

#include <UtH/Platform/FileReader.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Singleton.hpp>

#include <UtH/Resources/Font.hpp>
#include <UtH/Resources/Image.hpp>
#include <UtH/Resources/SoundBuffer.hpp>

#include <UtH/Renderer/Texture.hpp>

#include <unordered_map>
#include <utility>
#include <memory>

#define uthRS uth::ResourceManager::getInstance()

namespace uth
{
	class ResourceManager : public uth::Singleton<uth::ResourceManager>
	{
		friend class Singleton<uth::ResourceManager>;

	public:

        enum
        {
            SoundBuffers =	1,
            Images =		1 << 1,
            Textures =		1 << 2,
			Fonts =			1 << 3,

            All = SoundBuffers | Images | Textures | Fonts
        };

		SoundBuffer* LoadSoundBuffer(const std::string& filePath);
		Image* LoadImage(const std::string& filePath);
        Texture* LoadTexture(const std::string& filePath);
        Font* LoadFont(const std::string& filePath);

        void Clear(const unsigned int flags);
        bool DeleteSoundBuffer(const std::string& filePath);
        bool DeleteImage(const std::string& filePath);
        bool DeleteTexture(const std::string& filePath);
        bool DeleteFont(const std::string& filePath);

	private:
		ResourceManager();
		~ResourceManager();

        std::unordered_map<std::string, std::unique_ptr<SoundBuffer, SoundBuffer::Deleter>> m_soundBuffers;
		std::unordered_map<std::string, std::unique_ptr<Image, Image::Deleter>> m_images;
        std::unordered_map<std::string, std::unique_ptr<Texture, Texture::Deleter>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<Font, Font::Deleter>> m_fonts;
	};
}

#endif