#include <UtH/Resources/ResourceManager.h>

using namespace uth;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

SoundBuffer& ResourceManager::LoadWAV(const std::string& filePath)
{
    auto itr = m_soundBuffers.find(filePath);

    if (itr != m_soundBuffers.end())
        return *itr->second;

    SoundBuffer* temp = new SoundBuffer;
	const bool result = temp->LoadFromFile(filePath);
    assert(result);

    m_soundBuffers[filePath] = std::unique_ptr<SoundBuffer>(temp);

    return *temp;
}

Image& ResourceManager::LoadTGA(const std::string& filePath)
{
	auto itr = m_images.find(filePath);

    if (itr != m_images.end())
        return *itr->second;

    Image* temp = new Image();
    const bool result = temp->LoadFromFile(filePath);
	assert(result);

    m_images[filePath] = std::unique_ptr<Image>(temp);

    return *temp;
}

Texture& ResourceManager::LoadTexture(const std::string& filePath)
{
    auto itr = m_textures.find(filePath);

    if (itr != m_textures.end())
        return *itr->second;

    Texture* temp = new Texture();
    const bool result = temp->LoadFromFile(filePath);
	assert(result);

    m_textures[filePath] = std::unique_ptr<Texture>(temp);

    return *temp;
}

Font& ResourceManager::LoadFont(const std::string& filePath)
{
    auto itr = m_fonts.find(filePath);

    if (itr != m_fonts.end())
        return *itr->second;

    Font* temp = new Font();
    const bool result = temp->LoadFromFile(filePath);
	assert(result);

    m_fonts[filePath] = std::unique_ptr<Font>(temp);

    return *temp;
}

void ResourceManager::Clear(const unsigned int flags)
{
    if ((flags & uth::ResourceManager::SoundBuffers) != 0)
        m_soundBuffers.clear();
    if ((flags & uth::ResourceManager::Images) != 0)
        m_images.clear();
    if ((flags & uth::ResourceManager::Textures) != 0)
        m_textures.clear();
	if ((flags & uth::ResourceManager::Fonts) != 0)
        m_fonts.clear();
}

bool ResourceManager::DeleteSoundBuffer(const std::string& filePath)
{
    auto itr = m_soundBuffers.find(filePath);

    if (itr != m_soundBuffers.end())
    {
        m_soundBuffers.erase(itr);
        return true;
    }

    return false;
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
