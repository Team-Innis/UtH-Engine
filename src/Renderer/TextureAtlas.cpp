#include <UtH/Renderer/TextureAtlas.hpp>
#include <UtH/Platform/FileReader.h>
#include <UtH/Resources/ResourceManager.h>
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


    bool TextureAtlas::LoadFromFile(const std::string& filePath, const bool smooth, const bool repeated)
    {
        m_texture = &uthRS.LoadTexture(filePath);

        std::string s(filePath);
        unsigned int extensionStart = s.find_last_of('.') + 1;

        s.replace(extensionStart, s.length() - extensionStart, "xml");

        FileReader fr;
        fr.OpenFile(s.c_str());

        tinyxml2::XMLDocument doc;
        if (doc.Parse(fr.ReadText()))
            return false;

        tinyxml2::XMLElement* element = doc.FirstChildElement();

        for (const tinyxml2::XMLElement* child = element->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
        {
            std::string name(child->FindAttribute("name")->Value());
            umath::rectangle rect;

            float x = child->FindAttribute("x")->FloatValue(),
                  y = child->FindAttribute("y")->FloatValue();

            rect.left = x / m_texture->GetSize().w;
            rect.top = y / m_texture->GetSize().h;
            rect.width = child->FindAttribute("width")->FloatValue() / m_texture->GetSize().w;
            rect.height = child->FindAttribute("height")->FloatValue() / m_texture->GetSize().h;

            m_textureRects.insert(std::make_pair(name, rect));
        }
        return true;
    }

    void TextureAtlas::Bind()
    {
        m_texture->Bind();
    }

    unsigned int TextureAtlas::GetTextureID() const
    {
        return m_texture->GetTextureID();
    }

    bool TextureAtlas::SetSmooth(const bool value)
    {
        return m_texture->SetSmooth(value);
    }

    bool TextureAtlas::SetRepeated(const bool value)
    {
        return m_texture->SetRepeated(value);
    }

    const umath::vector2& TextureAtlas::GetSize() const
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

    bool TextureAtlas::IsRepeated() const
    {
        return m_texture->IsRepeated();
    }

    const umath::rectangle& TextureAtlas::getTextureCoords(const char* name) const
    {
        return m_textureRects.at(name);
    }
}