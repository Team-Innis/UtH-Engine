#include <cmath>
#include <UtH/Engine/Text.hpp>
#include <freetype-gl/freetype-gl.h>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

Text::Text(const std::string& fontPath, const float fontSize, const std::string& name)
	: Component(name),
	  m_fontSize(fontSize)
{
	SetDrawable(true);
	m_path = "assets/" + fontPath;

	m_textShader.LoadShader("shaders/text.vert", "shaders/text.frag");

	m_atlas = texture_atlas_new(1024, 1024, 1);
}

Text::~Text()
{
	texture_atlas_delete(m_atlas);
}


// Public

void Text::SetText(const std::wstring& text, umath::vector4& color)
{
	m_vertexBuffer.clear();
	m_lastPos = umath::vector2(0, 0);
	m_text = std::wstring();

	AddText(text, color);
}

void Text::AddText(const std::wstring& text, /*const float size, umath::vector2& position,*/ umath::vector4& color)
{
	m_text += text;

	texture_font_t* font = texture_font_new_from_file(m_atlas, m_fontSize, m_path.c_str());

	bool newLine = false;
	umath::vector2 pos = m_lastPos; //= position;

	for (size_t i = 0; i < text.length(); ++i)
	{
		texture_glyph_t* glyph = nullptr;
		if (text.at(i) == L'\n')
		{
			newLine = true;
			pos.y += m_fontSize;
			pos.x = 0;
		}
		else
			glyph = texture_font_get_glyph(font, text.at(i));

		if (glyph != nullptr)
		{
			int kerning = 0;
			if (i > 0 && !newLine)
				kerning = texture_glyph_get_kerning(glyph, text.at(i - 1));

			pos.x += kerning;

			const int x0 = pos.x + glyph->offset_x;
			const int y0 = pos.y - glyph->offset_y;
			const int x1 = x0 + glyph->width;
			const int y1 = y0 + glyph->height;
			
			const float s0 = glyph->s0; // Top left x
			const float t0 = glyph->t0; // Top left y
			const float s1 = glyph->s1; // Bottom right x
			const float t1 = glyph->t1; // Bottom right y


			m_vertexBuffer.addVertex(Vertex(umath::vector3(x0, y0, 0), umath::vector2(s0, t0), color));
			m_vertexBuffer.addVertex(Vertex(umath::vector3(x0, y1, 0), umath::vector2(s0, t1), color));
			m_vertexBuffer.addVertex(Vertex(umath::vector3(x1, y1, 0), umath::vector2(s1, t1), color));
			m_vertexBuffer.addVertex(Vertex(umath::vector3(x1, y0, 0), umath::vector2(s1, t0), color));


			std::vector<unsigned short> indices;
			indices.push_back(0);
			indices.push_back(1);
			indices.push_back(2);
			indices.push_back(0);
			indices.push_back(2);
			indices.push_back(3);
			m_vertexBuffer.addIndices(indices);

			pos.x += glyph->advance_x;
			newLine = false;
		}
	}

	m_lastPos = pos;

	texture_font_delete(font);
}

const std::wstring& Text::GetText() const
{
	return m_text;
}

void Text::Update(float dt)
{
	// No need for update
}

void Text::Draw(Shader* shader, Camera* camera)
{
	m_textShader.Use();

	uthGraphics.bindTexture(TEXTURE_2D, m_atlas->id);
	m_textShader.SetUniform("unifSampler", 0);

	m_textShader.SetUniform("unifModel", parent->transform.GetTransform());
	m_textShader.SetUniform("unifProjection", camera->GetProjectionTransform());

	m_vertexBuffer.draw(&m_textShader);
}