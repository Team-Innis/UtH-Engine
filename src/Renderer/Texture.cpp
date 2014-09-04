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

    Texture::Texture(const std::string& filePath)
        : m_textureID(0),
          m_size(),
          m_smooth(false),
          m_repeated(false)
    {
        LoadFromFile(filePath);
    }

    Texture::~Texture()
    {
		Delete();
    }
	
	void Texture::Delete()
	{
		uth::Graphics::DeleteTextures(1,&m_textureID);
	}


    bool Texture::Create(const umath::vector2& size, const bool smooth, const bool repeated)
    {
        if (size.x == 0 || size.y == 0)
            return false;

        m_size = size;

        uth::Graphics::SetPixelStore(UNPACK_ALIGNMENT, 1);
        uth::Graphics::GenerateTextures(1, &m_textureID);
        uth::Graphics::SetActiveTexUnit(TEXTURE_0);

        Bind();
		SetSmooth(smooth);
        SetRepeated(repeated);

        uth::Graphics::SetTextureImage2D(TEXTURE_2D, 0, RGBA_FORMAT,
			static_cast<unsigned int>(m_size.x), static_cast<unsigned int>(m_size.y),
			RGBA_FORMAT, UNSIGNED_BYTE_TYPE, nullptr);

        return true;
    }

    bool Texture::LoadFromFile(const std::string& filePath, const bool smooth, const bool repeated)
    {
        const Image* img = uthRS.LoadImage(filePath);

        if (!img)
            return false;

        m_size = img->GetSize();

        if (m_size.x == 0 || m_size.y == 0)
            return false;

        uth::Graphics::SetPixelStore(UNPACK_ALIGNMENT, 1);
        uth::Graphics::GenerateTextures(1, &m_textureID);
        uth::Graphics::SetActiveTexUnit(TEXTURE_0);

        Bind();
		SetSmooth(smooth);
        SetRepeated(repeated);

		ImageFormat format = img->GetDepth() == 4 ? RGBA_FORMAT : RGB_FORMAT;

        uth::Graphics::SetTextureImage2D(TEXTURE_2D, 0, format,
			static_cast<unsigned int>(m_size.x), static_cast<unsigned int>(m_size.y),
			format, UNSIGNED_BYTE_TYPE, &img->m_pixels[0]);
		
		return true;
    }

    void Texture::Bind() const
    {
        uth::Graphics::SetActiveTexUnit(TEXTURE_0);
        uth::Graphics::BindTexture(TEXTURE_2D, m_textureID);
    }

    void Texture::Unbind()
    {
        uth::Graphics::BindTexture(TEXTURE_2D, 0);
    }

    unsigned int Texture::GetTextureID() const
    {
        return m_textureID;
    }

    bool Texture::SetSmooth(const bool value)
    {
        if (!IsValid()) return false;

        Bind();

        uth::Graphics::SetTextureParameter(TEXTURE_2D, TEXTURE_MAG_FILTER, value ? LINEAR : NEAREST);
		uth::Graphics::SetTextureParameter(TEXTURE_2D, TEXTURE_MIN_FILTER, value ? LINEAR : NEAREST);

        m_smooth = value;

        return true;
    }

    bool Texture::SetRepeated(const bool value)
    {
        if (!IsValid()) return false;

        Bind();

        uth::Graphics::SetTextureParameter(TEXTURE_2D, TEXTURE_WRAP_S, value ? REPEAT : CLAMP_TO_EDGE);
        uth::Graphics::SetTextureParameter(TEXTURE_2D, TEXTURE_WRAP_T, value ? REPEAT : CLAMP_TO_EDGE);

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