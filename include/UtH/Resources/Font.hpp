#pragma once
#ifndef FONT_H_UTH
#define FONT_H_UTH

#include <string>

namespace uth
{
	class Font
	{
	private:
		struct FontStruct
        {
            void* fontData;
			int dataSize;

            ~FontStruct()
            {
                delete fontData;
            }

        } m_fontData;

	public:
		Font();
		Font(const std::string& filePath);
		~Font();

		bool LoadFromFile(const std::string& filePath);

		const FontStruct& GetFontData() const;
	};
}

#endif