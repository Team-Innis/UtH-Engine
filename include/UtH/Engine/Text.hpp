#pragma once
#ifndef TEXT_H_UTH
#define TEXT_H_UTH

#include <UtH/Engine/Component.hpp>
#include <UtH/Core/VertexBuffer.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <pmath/Vector.hpp>

// Forward declaration so we dont need to include the ugly C headers
struct texture_atlas_t;
struct texture_font_t;

namespace uth
{
	class Text : public Component
	{
	public:
		Text(const std::string& fontPath, const float fontSize, const std::string& name = "Text");
		~Text();

		void Init();

		// Sets the text
		void SetText(const std::string& text, const pmath::Vec4 color = pmath::Vec4(1, 1, 1, 1));
		void SetText(const std::wstring& text, const pmath::Vec4 color = pmath::Vec4(1, 1, 1, 1));
		// Adds to the current text
		void AddText(const std::string& text, const pmath::Vec4 color = pmath::Vec4(1, 1, 1, 1));
		void AddText(const std::wstring& text, const pmath::Vec4 color = pmath::Vec4(1, 1, 1, 1));
		// Return current text
		const std::wstring& GetText() const;

		void Draw(RenderTarget& target);

	private:
		//Text();
		Text(/*"text", path = "font", size = 32, name = "Text"*/);

		Shader m_textShader;

		VertexBuffer m_vertexBuffer;

		const float m_fontSize;
		pmath::Vec2 m_size;
		pmath::Mat4 m_matrix;

		std::wstring m_text;
		// last text cursor pos
		pmath::Vec2 m_lastPos;

		texture_atlas_t* m_atlas;
		texture_font_t* m_font;
	};
}

#endif