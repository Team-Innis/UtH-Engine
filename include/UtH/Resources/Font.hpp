#pragma once
#ifndef FONT_H_UTH
#define FONT_H_UTH

#include <string>
#include <UtH/Platform/BinaryData.hpp>

namespace uth
{
	class Font
	{
	private:

        struct Deleter
        {
            void operator()(Font* file) const
            {
                delete file;
            }
        };

        friend class ResourceManager;

    public:

        const BINARY_DATA& GetFontData() const;


    private:

		Font();
		~Font();

        bool LoadFromFile(const std::string& filePath);

        BINARY_DATA m_fontData;
	};
}

#endif