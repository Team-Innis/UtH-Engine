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
{ }

// Public
bool Font::LoadFromFile(const std::string& filePath)
{
	FileReader fr;
	fr.OpenFile(filePath.c_str());
	m_fontData.fontData = fr.ReadBinary();
	m_fontData.dataSize = fr.GetFileSize();

	if(m_fontData.fontData == nullptr)
		return false;

	return true;
}

const Font::FontStruct& Font::GetFontData() const
{
	return m_fontData;
}

// Private
Font::FontStruct::~FontStruct()
{
	delete[] fontData;
}