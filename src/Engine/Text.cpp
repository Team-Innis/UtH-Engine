#include <UtH/Engine/Text.hpp>
#include <freetype-gl/freetype-gl.h>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/Camera.hpp>

using namespace uth;

Text::Text(const std::string& fontPath, const std::string& name)
	: Component(name)
{
	SetDrawable(true);
	m_path = "assets/" + fontPath;

	m_textShader.LoadShader("shaders/text.vert", "shaders/text.frag");

	m_atlas = texture_atlas_new(1024, 1024, 1);
}

Text::~Text()
{

}


// Public

void Text::SetText(const std::wstring& text, const float size, /*umath::vector2& position,*/ umath::vector4& color)
{
	m_vertexBuffer.clear();

	m_text = text;

	texture_font_t* font = texture_font_new_from_file(m_atlas, size, m_path.c_str());
	texture_font_load_glyphs(font, m_text.c_str());

	umath::vector2 pos; //= position;

	for (size_t i = 0; i < m_text.length(); ++i)
	{
		texture_glyph_t* glyph = texture_font_get_glyph(font, m_text.at(i));
		if (glyph != nullptr)
		{
			int kerning = 0;
			if (i > 0)
				kerning = texture_glyph_get_kerning(glyph, m_text.at(i - 1));

			pos.x += kerning;

			const int x0 = pos.x + glyph->offset_x;
			const int y0 = pos.y + glyph->offset_y;
			const int x1 = x0 + glyph->width;
			const int y1 = y0 + glyph->height;
			const float s0 = glyph->s0;
			const float s1 = glyph->s1;
			const float t0 = glyph->t0;
			const float t1 = glyph->t1;

			m_vertexBuffer.addVertex(Vertex(umath::vector3(x0, y0, 0), umath::vector2(s0, t0), color));
			m_vertexBuffer.addVertex(Vertex(umath::vector3(x0, y1, 0), umath::vector2(s0, t1), color));
			m_vertexBuffer.addVertex(Vertex(umath::vector3(x1, y1, 0), umath::vector2(s1, t1), color));
			m_vertexBuffer.addVertex(Vertex(umath::vector3(x1, y0, 0), umath::vector2(s1, t0), color));

			const int offset = i * 4;
			m_vertexBuffer.addIndex(0+offset);
			m_vertexBuffer.addIndex(1+offset);
			m_vertexBuffer.addIndex(2+offset);
			m_vertexBuffer.addIndex(0+offset);
			m_vertexBuffer.addIndex(2+offset);
			m_vertexBuffer.addIndex(3+offset);

			pos.x += glyph->advance_x;
		}
	}

	texture_font_delete(font);
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