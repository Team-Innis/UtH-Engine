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
		BINARY_DATA m_fontData;


	public:
		Font();
		Font(const std::string& filePath);
		~Font();

		bool LoadFromFile(const std::string& filePath);

		const BINARY_DATA& GetFontData() const;
	};
}

#endif