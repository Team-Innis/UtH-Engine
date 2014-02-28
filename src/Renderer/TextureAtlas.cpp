#include <UtH\Renderer\TextureAtlas.hpp>
#include <UtH\Platform\FileReader.h>
#include <string>
#include <tinyxml2.h>


namespace uth
{
    TextureAtlas::TextureAtlas()
        : m_texture()
    {

    }

    TextureAtlas::TextureAtlas(const char* path)
        : m_texture(path)
    {
        LoadFromFile(path);
    }

    TextureAtlas::~TextureAtlas()
    {

    }


    bool TextureAtlas::LoadFromFile(const char* path, const bool smooth, const bool repeated)
    {
        if (!m_texture.LoadFromFile(path, smooth, repeated))
            return false;

        std::string s(path);
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

            rect.left = x / m_texture.GetSize().w;
            rect.top = y / m_texture.GetSize().h;
            rect.width = child->FindAttribute("width")->FloatValue() / m_texture.GetSize().w;
            rect.height = child->FindAttribute("height")->FloatValue() / m_texture.GetSize().h;

            m_textureRects.insert(std::make_pair(name, rect));
        }
    }

    void TextureAtlas::Bind()
    {
        m_texture.Bind();
    }

    unsigned int TextureAtlas::GetTextureID() const
    {
        return m_texture.GetTextureID();
    }

    bool TextureAtlas::SetSmooth(const bool value)
    {
        return m_texture.SetSmooth(value);
    }

    bool TextureAtlas::SetRepeated(const bool value)
    {
        return m_texture.SetRepeated(value);
    }

    const umath::vector2& TextureAtlas::GetSize() const
    {
        return m_texture.GetSize();
    }

    bool TextureAtlas::IsValid() const
    {
        return m_texture.IsValid();
    }

    bool TextureAtlas::IsSmooth() const
    {
        return m_texture.IsSmooth();
    }

    bool TextureAtlas::IsRepeated() const
    {
        return m_texture.IsRepeated();
    }
}