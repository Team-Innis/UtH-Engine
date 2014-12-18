#include <UtH/Engine/Text.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <UtH/Platform/Configuration.hpp>

#include <freetype-gl/freetype-gl.h>

#include <cmath>
//#include <locale>

namespace
{
	static uth::Shader* textShader;
}

using namespace uth;

std::unordered_set<Text*> Text::TEXTS;

uth::Text::Text(const std::string& fontPath, const float fontSize, 
	const std::string& name /*= "Text"*/, 
	const pmath::Vec4 defaultColor /*= pmath::Vec4(1,1,1,1)*/)
	: Component(name),
	m_fontSize(fontSize),
	m_size(0, m_fontSize),
    m_color(defaultColor)
{
	TEXTS.emplace(this);

	m_atlas = texture_atlas_new(1024, 1024, 1);

	m_uthFont = uthRS.LoadFont(fontPath);

    if (m_uthFont)
	{
        auto& data = m_uthFont->GetFontData();

		m_font = texture_font_new_from_memory(m_atlas, fontSize, data.ptr(), data.size());
	}
}

//uth::Text::Text()
//    : Component(),
//      m_fontSize(30)
//{
//
//}

Text::~Text()
{
	texture_font_delete(m_font);

	texture_atlas_delete(m_atlas);

	ClearOpenGLContext();

	TEXTS.erase(this);
}

void Text::Init()
{
	parent->transform.setSize(m_size);
}

void uth::Text::SetText(const std::string& text)
{
	SetText(text, m_color);
}
void uth::Text::SetText(const std::wstring& text)
{
	SetText(text, m_color);
}
void Text::SetText(const std::string& text, const pmath::Vec4 color)
{
	SetText(std::wstring(text.begin(), text.end()), color);
}
void Text::SetText(const std::wstring& text, const pmath::Vec4 color)
{
	m_size = pmath::Vec2(0, m_fontSize);
	m_vertexBuffer.clear();
	m_lastPos = pmath::Vec2(0, 0);
	m_text = std::wstring();

	AddText(text, color);
}

void uth::Text::AddText(const std::string& text)
{
	AddText(text, m_color);
}
void uth::Text::AddText(const std::wstring& text)
{
	AddText(text, m_color);
}
void Text::AddText(const std::string& text, const pmath::Vec4 color)
{
	AddText(std::wstring(text.begin(),text.end()),color);
}
void Text::AddText(const std::wstring& text, const pmath::Vec4 color)
{
	m_text += text;

	texture_font_load_glyphs(m_font, text.c_str());

	bool newLine = false;
	pmath::Vec2 pos = m_lastPos;

	for (size_t i = 0; i < text.length(); ++i)
	{
		texture_glyph_t* glyph = nullptr;
		if (text.at(i) == L'\n')
		{
			newLine = true;
			pos.y += m_fontSize;
			m_size.y = pos.y + m_fontSize;
			pos.x = 0;
		}
		else
			glyph = texture_font_get_glyph(m_font, text.at(i));

		if (glyph != nullptr)
		{
			float kerning = 0.f;
			if (i > 0 && !newLine)
				kerning = texture_glyph_get_kerning(glyph, text.at(i - 1));

			pos.x += kerning;

			const float x0 = pos.x + glyph->offset_x;
			const float y0 = pos.y + m_fontSize - glyph->offset_y;
			const float x1 = x0 + glyph->width;
			const float y1 = y0 + glyph->height;

			const float s0 = glyph->s0; // Top left x
			const float t0 = glyph->t0; // Top left y
			const float s1 = glyph->s1; // Bottom right x
			const float t1 = glyph->t1; // Bottom right y

			m_vertexBuffer.addVertex(Vertex(pmath::Vec3(x0, y0, 0), pmath::Vec2(s0, t0), color));
			m_vertexBuffer.addVertex(Vertex(pmath::Vec3(x0, y1, 0), pmath::Vec2(s0, t1), color));
			m_vertexBuffer.addVertex(Vertex(pmath::Vec3(x1, y1, 0), pmath::Vec2(s1, t1), color));
			m_vertexBuffer.addVertex(Vertex(pmath::Vec3(x1, y0, 0), pmath::Vec2(s1, t0), color));

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

			if (pos.x>m_size.x)
			{
				m_size.x=pos.x;
			}
		}
	}

	if (parent)
		parent->transform.setSize(m_size);

	m_matrix[0][0] = 1;
	m_matrix[1][1] = 1;
	m_matrix[0][3] = (-0.5f) * m_size.x;
	m_matrix[1][3] = (-0.5f) * m_size.y;

	m_lastPos = pos;
}

const std::wstring& Text::GetText() const
{
	return m_text;
}

void uth::Text::SetColor(const pmath::Vec4 color)
{
    m_color = color;
    const std::wstring tempStr(m_text);
    SetText(tempStr, color);
}
const pmath::Vec4 uth::Text::GetDefaultColor()
{
	return m_color;
}

rapidjson::Value uth::Text::save(rapidjson::MemoryPoolAllocator<>& alloc) const
{
    namespace rj = rapidjson;

    rj::Value val = Component::save(alloc);

    val.AddMember(rj::StringRef("fontSize"), m_fontSize, alloc);
    val.AddMember(rj::StringRef("fontPath"), rj::Value(uthRS.FilePath(m_uthFont, ResourceManager::Fonts).c_str(), alloc), alloc);

    rj::Value& colVal = val.AddMember(rj::StringRef("color"), rj::kArrayType, alloc)["color"];

    colVal.PushBack(m_color.r, alloc)
          .PushBack(m_color.g, alloc)
          .PushBack(m_color.b, alloc)
          .PushBack(m_color.a, alloc);

    if (!m_text.empty())
        val.AddMember(rj::StringRef("string"), rj::Value(std::string(m_text.begin(), m_text.end()).c_str(), alloc), alloc);

    return val;
}

bool uth::Text::load(const rapidjson::Value& doc)
{
    if (!Component::load(doc))
        return false;

    const rapidjson::Value& colVal = doc["color"];

    m_color.r = colVal[0u].GetDouble();
    m_color.g = colVal[1].GetDouble();
    m_color.b = colVal[2].GetDouble();
    m_color.a = colVal[3].GetDouble();

    if (doc.HasMember("string"))
        SetText(doc["string"].GetString());

    return true;
}

void Text::Draw(RenderTarget& target)
{
	static bool shaderLoaded = false;
	if (!shaderLoaded)
	{
		textShader = uthRS.LoadShader("Shaders/DefaultText.vert", "Shaders/DefaultText.frag");
		shaderLoaded = true;
	}

	target.Bind();
	textShader->Use();

	uth::Graphics::BindTexture(TEXTURE_2D, m_atlas->id);
	textShader->SetUniform("unifSampler", 0);

	textShader->SetUniform("unifModel", parent->transform.GetTransform() * m_matrix);
	textShader->SetUniform("unifProjection", target.GetCamera().GetProjectionTransform());

	m_vertexBuffer.bindArrayBuffer();
	// (position + uv + color) * sizeof(float)
	const int posOffset = (3 + 2 + 4)*sizeof(float);
	// position * sizeof(float)
	const int uvStart = 3*sizeof(float);
	// (position + uv) * sizeof(float)
	const int colorStart = (3 + 2)*sizeof(float);

	// Attribute name, number of components, datatype, bytes between first elements,
	// offset of first element in buffer
	textShader->setAttributeData("attrPosition", 3, FLOAT_TYPE, posOffset, (void*)0);
	textShader->setAttributeData("attrUV", 2, FLOAT_TYPE, posOffset, (void*)uvStart);
	textShader->setAttributeData("attrColor", 4, FLOAT_TYPE, posOffset, (void*)colorStart);

	m_vertexBuffer.bindElementBuffer();
	uth::Graphics::DrawElements(TRIANGLES, m_vertexBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);

	uth::Graphics::BindBuffer(ARRAY_BUFFER, 0);
}


bool Text::RecreateOpenGLContext()
{
	texture_atlas_upload(m_atlas);

	return true;
}
bool Text::ClearOpenGLContext()
{
	return true;
}
