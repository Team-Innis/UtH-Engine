#include <UtH/Resources/Font.hpp>
#include <UtH/Platform/FileManager.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <cstdlib> // free

using namespace uth;

Font::Font()
{

}

Font::~Font()
{
	m_fontData.clear();
}

bool Font::LoadFromFile(const std::string& filePath)
{
	FileManager fr;
	fr.OpenFile(filePath);
	m_fontData = fr.ReadBinary();

	if (!m_fontData.ptr())
		return false;
	m_loaded = true;
	return true;
}
void Font::Unload()
{

}
bool Font::EnsureLoaded()
{
	if (m_loaded)
		return true;
	const bool result = LoadFromFile(uthRS.FilePath(this, ResourceManager::Fonts));
	//assert(result);
	return result;
}

const BINARY_DATA& Font::GetFontData() const
{
	return m_fontData;
}
