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

    Texture::~Texture()
    {

    }


    bool Texture::loadFromFile(const char* path, const bool smooth, const bool repeated)
    {
        uthRS.loadTGA(path);

        m_size.w = uthRS.header.width;
        m_size.h = uthRS.header.height;

        uthGraphics.setPixelStore(UNPACK_ALIGNMENT, 1);
        uthGraphics.generateTextures(1, &m_textureID);
        uthGraphics.setActiveTexUnit(TEXTURE_0);

        bind();

		//setSmooth(smooth);
  //      setRepeated(repeated);

        uthGraphics.setTextureImage2D(TEXTURE_2D, 0, RGBA_FORMAT, m_size.w, m_size.h, RGBA_FORMAT, UNSIGNED_BYTE_TYPE, uthRS.header.pixels);
		
		setSmooth(smooth);
        setRepeated(repeated);
		
		return true;
    }

    void Texture::bind()
    {
        uthGraphics.setActiveTexUnit(TEXTURE_0);
        uthGraphics.bindTexture(TEXTURE_2D, m_textureID);
    }

    const unsigned int Texture::getTextureID() const
    {
        return m_textureID;
    }

    bool Texture::setSmooth(const bool value)
    {
        if (!isValid()) return false;

        bind();

        uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_MAG_FILTER, value ? LINEAR : NEAREST);
		uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_MIN_FILTER, value ? LINEAR : NEAREST);

        m_smooth = value;

        return true;
    }

    bool Texture::setRepeated(const bool value)
    {
        if (!isValid()) return false;

        bind();

        uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_WRAP_S, value ? REPEAT : CLAMP_TO_EDGE);
        uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_WRAP_T, value ? REPEAT : CLAMP_TO_EDGE);

        m_repeated = value;

        return true;
    }

    const umath::vector2& Texture::getSize() const
    {
        return m_size;
    }

    const bool Texture::isValid() const
    {
        return m_textureID > 0;
    }
        
    const bool Texture::isSmooth() const
    {
        return m_smooth;
    }

    const bool Texture::isRepeated() const
    {
        return m_repeated;
    }
}