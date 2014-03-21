#include <UtH/Resources/ResourceManager.h>
#include <cstdlib> // malloc etc...

using namespace uth;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}


const SoundBuffer& ResourceManager::LoadWAV(const std::string &filePath)
{
    auto itr = m_soundBuffers.find(filePath);

    if (itr != m_soundBuffers.end())
        return *itr->second;

    SoundBuffer* temp = new SoundBuffer;
    assert(temp->LoadFromFile(filePath));

    m_soundBuffers[filePath] = temp;

    return *temp;

}

const Image& ResourceManager::LoadTGA(const std::string &filePath)
{
	auto itr = m_images.find(filePath);

    if (itr != m_images.end())
        return *itr->second;

    Image* temp = new Image;
    assert(temp->LoadFromFile(filePath));

    m_images[filePath] = temp;

    return *temp;
}