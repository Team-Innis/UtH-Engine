#include <UtH/Resources/Image.hpp>
#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>
#include <cassert>


namespace uth
{

    Image::Image()
        : m_size(),
          m_pixels(nullptr),
          m_depth(0)
    {}

    Image::Image(const std::string& filePath)
        : m_size(),
          m_pixels(nullptr),
          m_depth(0)
    {
        LoadFromFile(filePath);
    }

    Image::~Image()
    {
        delete[] m_pixels;
    }


    bool Image::LoadFromFile(const std::string& filePath)
    {
        FileReader FR(filePath.c_str());
        BYTE* buffer;

		buffer = new BYTE[4];
		FR.FileSeek(12, 0);
		FR.ReadBytes(buffer, 4);
		m_size.x = static_cast<float>((buffer[0] + buffer[1] * 256));
		m_size.y = static_cast<float>((buffer[2] + buffer[3] * 256));
		delete[] buffer;

		//bpp
		buffer = new BYTE[1];
		FR.FileSeek(16, 0);
		FR.ReadBytes(buffer, 1);
		m_depth = buffer[0];
		assert(m_depth == 24 || m_depth == 32);
		delete[] buffer;

		//data
		int datasize = static_cast<int>(m_size.x * m_size.y * m_depth / 8);
		m_pixels = new BYTE[datasize];
		buffer = new BYTE[datasize];
		FR.FileSeek(18, 0);
		FR.ReadBytes(buffer, datasize);

		//(pixels) rgb = bgr(tga)
		for(int i = 0; i < datasize; i+=4)
		{
			m_pixels[i+0] = buffer[i+2];
			m_pixels[i+1] = buffer[i+1];
			m_pixels[i+2] = buffer[i+0];
			m_pixels[i+3] = buffer[i+3];
		}
		delete[] buffer;

        return true;
    }

    const umath::vector2& Image::GetSize() const
    {
        return m_size;
    }

	BYTE Image::GetDepth() const
	{
		return m_depth;
	}


    umath::vector4 Image::GetPixel(unsigned int x, unsigned int y) const
    {
        assert(x > m_size.x || y > m_size.y);

        const unsigned int start = static_cast<unsigned int>(4 * ((y * m_size.x) + x));

        return umath::vector4(static_cast<float>(m_pixels[start]),
                              static_cast<float>(m_pixels[start + 1]),
                              static_cast<float>(m_pixels[start + 2]),
                              static_cast<float>(m_pixels[start + 3]));
    }

}