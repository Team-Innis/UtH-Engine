#pragma once
#ifndef RESOURCEMANAGER_H_UTH
#define RESOURCEMANAGER_H_UTH

#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Singleton.hpp>
#include <UtH/Resources/Image.hpp>
#include <UtH/Resources/SoundBuffer.hpp>

#include <unordered_map>
#include <utility>

#define uthRS uth::ResourceManager::getInstance()

namespace uth
{
	class ResourceManager : public uth::Singleton<uth::ResourceManager>
	{

		friend class Singleton<uth::ResourceManager>;

	public:

		const SoundBuffer& LoadWAV(const std::string &filePath);
		const Image& LoadTGA(const std::string &filePath);

	private:
		ResourceManager();
		~ResourceManager();

		std::unordered_map<std::string, SoundBuffer*> m_soundBuffers;
		std::unordered_map<std::string, Image*> m_images;
		
	};
}

#endif