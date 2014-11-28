#pragma once
#ifndef FONT_H_UTH
#define FONT_H_UTH

#include <string>
#include <UtH/Platform/BinaryData.hpp>
#include <UtH/Resources/Resource.hpp>
#include <map>

struct texture_atlas_t;
struct texture_font_t;

namespace uth
{
	class Font : public Resource
	{
	private:
		struct freetypeFont
		{
			texture_font_t* font;
			texture_atlas_t* atlas;
		};

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

		bool LoadFromFile(const std::string& filePath) override;
		void Unload() override;
		bool EnsureLoaded() override;


		BINARY_DATA m_fontData;

		std::map<int, freetypeFont> m_fonts;

		const int GetTexture(const int size) const;

		texture_font_t* GetFont(const int size);

	};
}

#endif