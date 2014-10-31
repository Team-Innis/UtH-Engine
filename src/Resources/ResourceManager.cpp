#include <UtH/Resources/ResourceManager.hpp>
#include <cassert>

using namespace uth;

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
        return itr->second.get();

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
        return itr->second.get();

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
        return itr->second.get();

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
		return itr->second.get();

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
}
bool uth::ResourceManager::UnloadImage(const std::string& filePath)
{
	auto& i = m_images.find(filePath);
	if (i == m_images.end())
		return false;

	i->second->Unload();
	return true;
}
bool uth::ResourceManager::UnloadTexture(const std::string& filePath)
{
	auto& i = m_textures.find(filePath);
	if (i == m_textures.end())
		return false;

	i->second->Unload();
	return true;
}
bool uth::ResourceManager::UnloadFont(const std::string& filePath)
{
	auto& i = m_fonts.find(filePath);
	if (i == m_fonts.end())
		return false;

	i->second->Unload();
	return true;
}
bool uth::ResourceManager::UnloadSound(const std::string& filePath)
{
	auto& i = m_sounds.find(filePath);
	if (i == m_sounds.end())
		return false;

	i->second->Unload();
	return true;
}

bool uth::ResourceManager::RecreateOpenGLContext()
{
	for (auto& i : m_images)
		i.second->EnsureLoaded();
	for (auto& i : m_textures)
		i.second->EnsureLoaded();

	return true;
}
bool uth::ResourceManager::ClearOpenGLContext()
{
	Unload(Textures);
	return true;
}

void ResourceManager::PauseSounds()
{
	int size = m_sounds.size();
	auto itr = m_sounds.begin();

	for (int i = 0; i < size; i++)
	{
		itr->second->Pause();
		itr++;
	}
}

const std::string& ResourceManager::FilePath(const void* ptr, const unsigned int flags) const
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
	return nullptr;
}

