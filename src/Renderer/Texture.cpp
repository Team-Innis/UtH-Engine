#include <UtH/Renderer/Texture.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Resources/ResourceManager.h>
#include <cstdlib>


namespace uth
{
    Texture::Texture()
        : m_textureID(0),
          m_size(),
          m_smooth(false),
          m_repeated(false)
    {

    }

    Texture::Texture(const char* path)
        : m_textureID(0),
          m_size(),
          m_smooth(false),
          m_repeated(false)
    {
        LoadFromFile(path);
    }

    Texture::~Texture()
    {

    }


    bool Texture::LoadFromFile(const char* path, const bool smooth, const bool repeated)
    {
        uthRS.loadTGA(path);

        m_size.w = uthRS.header.width;
        m_size.h = uthRS.header.height;

        if (m_size.w == 0 || m_size.h == 0)
            return false;

        uthGraphics.setPixelStore(UNPACK_ALIGNMENT, 1);
        uthGraphics.generateTextures(1, &m_textureID);
        uthGraphics.setActiveTexUnit(TEXTURE_0);

        Bind();

        uthGraphics.setTextureImage2D(TEXTURE_2D, 0, RGBA_FORMAT, m_size.w, m_size.h, RGBA_FORMAT, UNSIGNED_BYTE_TYPE, uthRS.header.pixels);
		
		SetSmooth(smooth);
        SetRepeated(repeated);
		
		return true;
    }

    void Texture::Bind()
    {
        uthGraphics.setActiveTexUnit(TEXTURE_0);
        uthGraphics.bindTexture(TEXTURE_2D, m_textureID);
    }

    unsigned int Texture::GetTextureID() const
    {
        return m_textureID;
    }

    bool Texture::SetSmooth(const bool value)
    {
        if (!IsValid()) return false;

        Bind();

        uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_MAG_FILTER, value ? LINEAR : NEAREST);
		uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_MIN_FILTER, value ? LINEAR : NEAREST);

        m_smooth = value;

        return true;
    }

    bool Texture::SetRepeated(const bool value)
    {
        if (!IsValid()) return false;

        Bind();

        uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_WRAP_S, value ? REPEAT : CLAMP_TO_EDGE);
        uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_WRAP_T, value ? REPEAT : CLAMP_TO_EDGE);

        m_repeated = value;

        return true;
    }

    const umath::vector2& Texture::GetSize() const
    {
        return m_size;
    }

    bool Texture::IsValid() const
    {
        return m_textureID > 0;
    }
        
    bool Texture::IsSmooth() const
    {
        return m_smooth;
    }

    bool Texture::IsRepeated() const
    {
        return m_repeated;
    }
}