#include <UtH/Resources/Font.hpp>
#include <UtH/Platform/FileManager.hpp>
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

bool Font::Unload()
{

}

const BINARY_DATA& Font::GetFontData() const
{
	return m_fontData;
}
