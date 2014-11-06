#pragma once
#ifndef RESOURCEMANAGER_H_UTH
#define RESOURCEMANAGER_H_UTH

#include <UtH/Platform/FileManager.hpp>
#include <UtH/Audio/Sound.hpp>

#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Singleton.hpp>

#include <UtH/Resources/Font.hpp>
#include <UtH/Resources/Image.hpp>

#include <UtH/Renderer/Texture.hpp>

#include <UtH/Core/Shader.hpp>

#include <unordered_map>
#include <utility>
#include <memory>

#define uthRS uth::ResourceManager::getInstance()

namespace uth
{
	class ResourceManager : public uth::Singleton<uth::ResourceManager>
	{
		friend class Singleton<uth::ResourceManager>;
		friend class Resource;

	public:

        enum
        {
            Sounds =	1,
            Images =		1 << 1,
            Textures =		1 << 2,
			Fonts =			1 << 3,
			Shaders =		1 << 4,

            All = Sounds | Images | Textures | Fonts | Shaders
        };

		Image* LoadImage(const std::string& filePath);
        Texture* LoadTexture(const std::string& filePath);
        Font* LoadFont(const std::string& filePath);
		Sound* LoadSound(const std::string& filePath);
		Shader* LoadShader(const std::string& vertexPath, const std::string& fragmentPath);

		void Clear(const unsigned int flags);
		bool DeleteImage(const std::string& filePath);
		bool DeleteTexture(const std::string& filePath);
		bool DeleteFont(const std::string& filePath);
		bool DeleteSound(const std::string& filePath);
		bool DeleteShader(const std::string& vertexPath, const std::string& fragmentPath);

		void Unload(const unsigned int flags);
		bool UnloadImage(const std::string& filePath);
		bool UnloadTexture(const std::string& filePath);
		bool UnloadFont(const std::string& filePath);
		bool UnloadSound(const std::string& filePath);
		bool UnloadShader(const std::string& vertexPath, const std::string& fragmentPath);

		bool ClearOpenGLContext();
		bool RecreateOpenGLContext();

		void PauseSounds();

	private:
		ResourceManager();
		~ResourceManager();

		const std::string FilePath(const void* ptr, const unsigned int flags) const;

		std::unordered_map<std::string, std::unique_ptr<Image, Image::Deleter>> m_images;
        std::unordered_map<std::string, std::unique_ptr<Texture, Texture::Deleter>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<Font, Font::Deleter>> m_fonts;
		std::unordered_map<std::string, std::unique_ptr<Sound, Sound::Deleter>> m_sounds;
		std::unordered_map<std::string, std::unique_ptr<Shader, Shader::Deleter>> m_shaders;

	};
}

#endif