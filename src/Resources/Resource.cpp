#include <UtH/Resources/Resource.hpp>
#include <UtH/Resources/ResourceManager.hpp>

using namespace uth;

Resource::Resource()
	: m_loaded(false)
{

}

bool Resource::IsLoaded() const
{
	return m_loaded;
}

bool Resource::EnsureLoaded()
{
	if (m_loaded)
		return true;
	const bool result = LoadFromFile(uthRS.FilePath(this, ResourceManager::All));
	//assert(result);
	return result;
}
