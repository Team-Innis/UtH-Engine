#include <UtH/Renderer/TextureAtlas.hpp>
#include <UtH/Platform/FileManager.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <string>
#include <tinyxml2.h>


namespace uth
{
	TextureAtlas::TextureAtlas()
		: m_texture(nullptr)
	{

	}

	TextureAtlas::TextureAtlas(const std::string& filePath)
		: m_texture(nullptr)
	{
		LoadFromFile(filePath);
	}

	TextureAtlas::~TextureAtlas()
	{

	}


	bool TextureAtlas::LoadFromFile(const std::string& filePath)
	{
		FileManager fr;
		fr.OpenFile(filePath);

		tinyxml2::XMLDocument doc;
		if (doc.Parse(fr.ReadText().c_str()))
			return false;

		const tinyxml2::XMLElement* element = doc.FirstChildElement();
		m_texture = uthRS.LoadTexture(element->FindAttribute("imagePath")->Value());

        if (!m_texture)
            return false;

		for (const tinyxml2::XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
		{
			std::string name(child->FindAttribute("name")->Value());
			pmath::Rect rect;

			float x = child->FindAttribute("x")->FloatValue(),
				y = child->FindAttribute("y")->FloatValue();

			rect.position.x = x / m_texture->GetSize().x;
			rect.position.y = y / m_texture->GetSize().y;
			rect.size.x = child->FindAttribute("width")->FloatValue() / m_texture->GetSize().x;
			rect.size.y = child->FindAttribute("height")->FloatValue() / m_texture->GetSize().y;

			m_textureRects.insert(std::make_pair(name, rect));
		}
		return true;
	}

	void TextureAtlas::Bind()
	{
		m_texture->Bind();
	}

	/*unsigned int TextureAtlas::GetTextureID() const
	{
		return m_texture->GetTextureID();
	}*/

	bool TextureAtlas::SetSmooth(const bool value)
	{
		return m_texture->SetSmooth(value);
	}

	const pmath::Vec2& TextureAtlas::GetSize() const
	{
		return m_texture->GetSize();
	}

	bool TextureAtlas::IsValid() const
	{
		return m_texture->IsValid();
	}

	bool TextureAtlas::IsSmooth() const
	{
		return m_texture->IsSmooth();
	}

	const pmath::Rect& TextureAtlas::getTextureCoords(const char* name) const
	{
		return m_textureRects.at(name);
	}
}