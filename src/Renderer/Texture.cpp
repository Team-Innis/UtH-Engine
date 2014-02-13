#include <UtH\Renderer\Texture.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Platform\FileReader.h>
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
        unsigned char* pixels;
	
		FileReader FR(path);
	
		unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char)*4);

		if (!FR.FileSeek(12, 0)) return false;
		FR.ReadBytes(buffer, 4);
		int sizeX= buffer[0]+buffer[1]*256;
		int sizeY= buffer[2]+buffer[3]*256;
		free(buffer);
	
		buffer = (unsigned char*)malloc(sizeof(unsigned char) * 1);
		FR.FileSeek(16, 0);
		FR.ReadBytes(buffer, 1);
		int bpp = buffer[0];
		free(buffer);
	
		int datasize = sizeX * sizeY * bpp / 8;
		pixels = (unsigned char*)malloc(sizeof(unsigned char) * datasize);
		unsigned char* t_buffer = (unsigned char*)malloc(sizeof(unsigned char) * datasize);
	
		FR.FileSeek(18, 0);
		FR.ReadBytes(t_buffer, datasize);	
		for(int i = 0; i < datasize; i += 4)
		{
			pixels[i + 0] = t_buffer[i + 2];
			pixels[i + 1] = t_buffer[i + 1];
			pixels[i + 2] = t_buffer[i + 0];
			pixels[i + 3] = t_buffer[i + 3];
		}

        uthGraphics.setPixelStore(UNPACK_ALIGNMENT, 1);
        uthGraphics.generateTextures(1, &m_textureID);
        uthGraphics.setActiveTexUnit(TEXTURE_0);

        bind();

        uthGraphics.setTextureImage2D(TEXTURE_2D, 0, RGBA_FORMAT, sizeX, sizeY, RGBA_FORMAT,
                     UNSIGNED_BYTE_TYPE, pixels);

        setSmooth(smooth);
        setRepeated(repeated);

        return true;
    }

    void Texture::bind()
    {
        uthGraphics.bindTexture(TEXTURE_2D, m_textureID);
    }

    const unsigned int Texture::getTextureID() const
    {
        return m_textureID;
    }

    bool Texture::setSmooth(const bool value)
    {
        if (isValid()) return false;

        if (m_smooth != value)
        {
            bind();

            uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_MAG_FILTER, m_smooth ? LINEAR : NEAREST);
		    uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_MIN_FILTER, m_smooth ? LINEAR : NEAREST);

            m_smooth = value;
        }

        return true;
    }

    bool Texture::setRepeated(const bool value)
    {
        if (!isValid()) return false;

        if (m_smooth != value)
        {
            bind();

            uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_WRAP_S, m_repeated ? REPEAT : CLAMP_TO_EDGE);
            uthGraphics.setTextureParameter(TEXTURE_2D, TEXTURE_WRAP_T, m_repeated ? REPEAT : CLAMP_TO_EDGE);

            m_repeated = value;
        }

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