#pragma once
#ifndef RESOURCEMANAGER_H_UTH
#define RESOURCEMANAGER_H_UTH

#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Singleton.hpp>
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
            SoundBuffers = 1,
            Images = 1 << 1,
            Textures = 1 << 2,


            All = SoundBuffers | Images | Textures
        };



		SoundBuffer& LoadWAV(const std::string& filePath);
		Image& LoadTGA(const std::string& filePath);
        Texture& LoadTexture(const std::string& filePath);


        void Clear(const unsigned int flags);
        bool DeleteSoundBuffer(const std::string& filePath);
        bool DeleteImage(const std::string& filePath);
        bool DeleteTexture(const std::string& filePath);


	private:
		ResourceManager();
		~ResourceManager();

        std::unordered_map<std::string, std::unique_ptr<SoundBuffer>> m_soundBuffers;
		std::unordered_map<std::string, std::unique_ptr<Image>> m_images;
        std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
		
	};
}

#endif