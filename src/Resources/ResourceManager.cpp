#include <UtH/Resources/ResourceManager.hpp>
#include <UtH/Renderer/VertexBuffer.hpp>
#include <UtH/Engine/SceneManager.hpp>
#include <UtH/Engine/Text.hpp>
#include <cassert>

using namespace uth;

namespace
{
	std::string combineShaderPaths(const std::string& vertexPath, const std::string& fragmentPath)
	{
		return vertexPath + '\n' + fragmentPath;
	}
}

ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

Image* uth::ResourceManager::LoadImage(const std::string& filePath)
{
	auto itr = m_images.find(filePath);

	if (itr != m_images.end())
	{
		itr->second->EnsureLoaded();
		return itr->second.get();
	}

    std::unique_ptr<Image, Image::Deleter> temp(new Image());
    const bool result = temp->LoadFromFile(filePath);

    if (result)
    {
        auto tempPtr = temp.get();
        m_images[filePath] = std::unique_ptr<Image, Image::Deleter>(temp.release());
        return tempPtr;
    }

    return nullptr;
}
Texture* uth::ResourceManager::LoadTexture(const std::string& filePath)
{
    auto itr = m_textures.find(filePath);

	if (itr != m_textures.end())
	{
		itr->second->EnsureLoaded();
		return itr->second.get();
	}

    std::unique_ptr<Texture, Texture::Deleter> temp(new Texture());
    const bool result = temp->LoadFromFile(filePath);

    if (result)
    {
        auto tempPtr = temp.get();
        m_textures[filePath] = std::unique_ptr<Texture, Texture::Deleter>(temp.release());
        return tempPtr;
    }

    return nullptr;
}
Font* ResourceManager::LoadFont(const std::string& filePath)
{
    auto itr = m_fonts.find(filePath);

	if (itr != m_fonts.end())
	{
		itr->second->EnsureLoaded();
		return itr->second.get();
	}

    std::unique_ptr<Font, Font::Deleter> temp(new Font());
    const bool result = temp->LoadFromFile(filePath);

    if (result)
    {
        auto tempPtr = temp.get();
        m_fonts[filePath] = std::unique_ptr<Font, Font::Deleter>(temp.release());
        return tempPtr;
    }

    return nullptr;
}
Sound* ResourceManager::LoadSound(const std::string& filePath)
{
	auto itr = m_sounds.find(filePath);

	if (itr != m_sounds.end())
	{
		itr->second->EnsureLoaded();
		return itr->second.get();
	}

	std::unique_ptr<Sound, Sound::Deleter> temp(new Sound());
	const bool result = temp->LoadFromFile(filePath);

	if (result)
	{
		auto tempPtr = temp.get();
		m_sounds[filePath] = std::unique_ptr<Sound, Sound::Deleter>(temp.release());
		return tempPtr;
	}

	return nullptr;
}
Shader* ResourceManager::LoadShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	const std::string filePath = combineShaderPaths(vertexPath,fragmentPath);
	auto itr = m_shaders.find(filePath);

	if (itr != m_shaders.end())
	{
		itr->second->EnsureLoaded();
		return itr->second.get();
	}

	std::unique_ptr<Shader, Shader::Deleter> temp(new Shader());
	const bool result = temp->LoadFromFile(filePath);

	if (result)
	{
		auto tempPtr = temp.get();
		m_shaders[filePath] = std::unique_ptr<Shader, Shader::Deleter>(temp.release());
		return tempPtr;
	}

	return nullptr;
}

void ResourceManager::Clear(const unsigned int flags)
{
    if ((flags & uth::ResourceManager::Sounds) != 0)
        m_sounds.clear();
    if ((flags & uth::ResourceManager::Images) != 0)
        m_images.clear();
    if ((flags & uth::ResourceManager::Textures) != 0)
		m_textures.clear();
	if ((flags & uth::ResourceManager::Fonts) != 0)
		m_fonts.clear();
	if ((flags & uth::ResourceManager::Shaders) != 0)
		m_shaders.clear();
}
bool ResourceManager::DeleteImage(const std::string& filePath)
{
    auto itr = m_images.find(filePath);

    if (itr != m_images.end())
    {
        m_images.erase(itr);
        return true;
    }

    return false;
}
bool ResourceManager::DeleteTexture(const std::string& filePath)
{
    auto itr = m_textures.find(filePath);

    if (itr != m_textures.end())
    {
        m_textures.erase(itr);
        return true;
    }

    return false;
}
bool ResourceManager::DeleteFont(const std::string& filePath)
{
	auto itr = m_fonts.find(filePath);

    if (itr != m_fonts.end())
    {
        m_fonts.erase(itr);
        return true;
    }

    return false;
}
bool ResourceManager::DeleteSound(const std::string& filePath)
{
	auto itr = m_sounds.find(filePath);

	if (itr != m_sounds.end())
	{
		m_sounds.erase(itr);
		return true;
	}

	return false;
}
bool ResourceManager::DeleteShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	const std::string filePath = combineShaderPaths(vertexPath, fragmentPath);
	auto itr = m_shaders.find(filePath);

	if (itr != m_shaders.end())
	{
		m_shaders.erase(itr);
		return true;
	}

	return false;
}


void uth::ResourceManager::Unload(const unsigned int flags)
{
	if ((flags & uth::ResourceManager::Sounds) != 0)
		for (auto& i : m_sounds)
			i.second->Unload();
	if ((flags & uth::ResourceManager::Images) != 0)
		for (auto& i : m_images)
			i.second->Unload();
	if ((flags & uth::ResourceManager::Textures) != 0)
		for (auto& i : m_textures)
			i.second->Unload();
	if ((flags & uth::ResourceManager::Fonts) != 0)
		for (auto& i : m_fonts)
			i.second->Unload();
	if ((flags & uth::ResourceManager::Shaders) != 0)
		for (auto& i : m_shaders)
			i.second->Unload();
}
bool uth::ResourceManager::UnloadImage(const std::string& filePath)
{
	auto i = m_images.find(filePath);
	if (i == m_images.end())
		return false;

	i->second->Unload();
	return true;
}
bool uth::ResourceManager::UnloadTexture(const std::string& filePath)
{
	auto i = m_textures.find(filePath);
	if (i == m_textures.end())
		return false;

	i->second->Unload();
	return true;
}
bool uth::ResourceManager::UnloadFont(const std::string& filePath)
{
	auto i = m_fonts.find(filePath);
	if (i == m_fonts.end())
		return false;

	i->second->Unload();
	return true;
}
bool uth::ResourceManager::UnloadSound(const std::string& filePath)
{
	auto i = m_sounds.find(filePath);
	if (i == m_sounds.end())
		return false;

	i->second->Unload();
	return true;
}
bool uth::ResourceManager::UnloadShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	const std::string filePath = combineShaderPaths(vertexPath, fragmentPath);
	auto i = m_shaders.find(filePath);
	if (i == m_shaders.end())
		return false;

	i->second->Unload();
	return true;
}

bool uth::ResourceManager::RecreateOpenGLContext()
{
	WriteLog("Recreating context");
	for (auto& i : m_textures)
		i.second->EnsureLoaded();
	for (auto& i : m_shaders)
		i.second->EnsureLoaded();

	for (auto it : VertexBuffer::VERTEXBUFFERS)
		it->RecreateOpenGLContext();
	for (auto it : Text::TEXTS)
		it->RecreateOpenGLContext();

	uthSceneM.AndroidReturn();

	return true;
}
bool uth::ResourceManager::ClearOpenGLContext()
{
	uthSceneM.AndroidLeave();

	WriteLog("Clearing context");
	bool result = true;
	Unload(Textures | Shaders);

	{
		//const auto temp = std::unordered_set<VertexBuffer*>(
		//	VertexBuffer::VERTEXBUFFERS.begin(),
		//	VertexBuffer::VERTEXBUFFERS.end());
		for (auto it : VertexBuffer::VERTEXBUFFERS)
			if (!it->ClearOpenGLContext())
				result = false;
	}

	return result;
}

void ResourceManager::PauseSounds(bool pause)
{
	int size = m_sounds.size();
	auto itr = m_sounds.begin();

	for (int i = 0; i < size; i++)
	{
		if (pause && itr->second->Status() == AL_PLAYING)
		{
			itr->second->Pause();
			itr->second->enginePaused = true;
		}
		else if (!pause && itr->second->enginePaused)
		{
			itr->second->Pause();
			itr->second->enginePaused = false;
		}
		itr++;
	}
}

const std::string ResourceManager::FilePath(const void* ptr, const unsigned int flags) const
{
	if ((flags & uth::ResourceManager::Sounds) != 0)
		for (auto& i : m_sounds)
			if (i.second.get() == ptr)
				return i.first;
	if ((flags & uth::ResourceManager::Images) != 0)
		for (auto& i : m_images)
			if (i.second.get() == ptr)
				return i.first;
	if ((flags & uth::ResourceManager::Textures) != 0)
		for (auto& i : m_textures)
			if (i.second.get() == ptr)
				return i.first;
	if ((flags & uth::ResourceManager::Fonts) != 0)
		for (auto& i : m_fonts)
			if (i.second.get() == ptr)
				return i.first;
	if ((flags & uth::ResourceManager::Shaders) != 0)
		for (auto& i : m_shaders)
			if (i.second.get() == ptr)
				return i.first;
	return "";
}

