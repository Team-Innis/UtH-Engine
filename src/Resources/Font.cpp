#include <UtH/Resources/Font.hpp>
#include <UtH/Platform/FileReader.h>
#include <cstdlib> // free

using namespace uth;

Font::Font()
{ }

Font::Font(const std::string& filePath)
{
	LoadFromFile(filePath);
}


Font::~Font()
{
	m_fontData.clear();
}

// Public
bool Font::LoadFromFile(const std::string& filePath)
{
	FileReader fr;
	fr.OpenFile(filePath.c_str());
	m_fontData = fr.ReadBinary();

	if(m_fontData.ptr() == nullptr)
		return false;

	return true;
}

const BINARY_DATA& Font::GetFontData() const
{
	return m_fontData;
}
