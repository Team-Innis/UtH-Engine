#pragma once
#ifndef TEXT_H_UTH
#define TEXT_H_UTH

#include <UtH/Engine/Component.hpp>
#include <UtH/Math/Vector.hpp>
#include <UtH/Core/VertexBuffer.hpp>

// Forward declaration so we dont need to include the ugly C headers
struct texture_atlas_t;

namespace uth
{
	class Text : public Component
	{
	public:
		Text(const std::string& fontPath, const float fontSize, const std::string& name = "Text");
		~Text();

		// Sets the text
		void SetText(const std::wstring& text, umath::vector4 color = umath::vector4(1, 1, 1, 1));
		// Adds to the current text
		void AddText(const std::wstring& text, umath::vector4 color = umath::vector4(1, 1, 1, 1));
		// Return current text
		const std::wstring& GetText() const;

		void Draw(RenderTarget& target);

	private:
		Text();

		Shader m_textShader;

		VertexBuffer m_vertexBuffer;

		std::string m_path;
		const float m_fontSize;

		std::wstring m_text;
		umath::vector2 m_lastPos;

		texture_atlas_t* m_atlas;
	};
}

#endif