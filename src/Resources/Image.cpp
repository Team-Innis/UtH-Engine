#include <UtH/Resources/Image.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/BinaryData.hpp>
#include <UtH/Platform/FileReader.hpp>
#include <cassert>
#include <cstring>
#include <vector>
#include <algorithm>

#pragma warning(push, 1)
#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"
#pragma warning(pop)


namespace uth
{

    Image::Image()
        : m_size(),
          m_pixels(),
          m_depth(0)
    {}

    Image::Image(const std::string& filePath)
        : m_size(),
          m_pixels(),
          m_depth(0)
    {
        LoadFromFile(filePath);
    }

    Image::~Image()
    {
        
    }


    bool Image::LoadFromFile(const std::string& filePath)
    {
        m_pixels.clear();

        int width, height, depth;
        FileReader fr(filePath);
        BINARY_DATA data = fr.ReadBinary();
        BYTE* pointer = stbi_load_from_memory(static_cast<stbi_uc*>(data.ptr()), data.size(), &width, &height, &depth, NULL);
        data.clear();

        if (pointer && width && height)
        {
            m_size.x = static_cast<float>(width);
            m_size.y = static_cast<float>(height);
            m_depth = static_cast<BYTE>(depth);

            m_pixels.resize(width * height * depth);

            // Flip the pixels horizontally into OpenGL format.
            for (int i = 0; i < height; ++i)
            {
                std::memcpy(&m_pixels[i * width * depth],
                            &pointer[m_pixels.size() - (i * width * depth) - width * depth],
                            width * depth);
            }

            stbi_image_free(pointer);
        }
        else
        {
            return false;
        }

        return true;
    }

    const pmath::Vec2& Image::GetSize() const
    {
        return m_size;
    }

	BYTE Image::GetDepth() const
	{
		return m_depth;
	}


    pmath::Vec4 Image::GetPixel(unsigned int x, unsigned int y) const
    {
        assert(x < m_size.x && y < m_size.y);

        const unsigned int start = static_cast<unsigned int>(4 * ((y * m_size.x) + x));

        return pmath::Vec4(static_cast<float>(m_pixels[start]),
                              static_cast<float>(m_pixels[start + 1]),
                              static_cast<float>(m_pixels[start + 2]),
                              static_cast<float>(m_pixels[start + 3]));
    }

    void Image::flipVertical()
    {
        if (!m_pixels.empty())
        {
            std::size_t rowSize = static_cast<std::size_t>(m_size.x) * 4;

            std::vector<BYTE>::iterator top = m_pixels.begin();
            std::vector<BYTE>::iterator bottom = m_pixels.end() - rowSize;

            for (std::size_t y = 0; y < m_size.y / 2; ++y)
            {
                std::swap_ranges(top, top + rowSize, bottom);

                top += rowSize;
                bottom -= rowSize;
            }
        }
    }

    void Image::flipHorizontal()
    {
        if (!m_pixels.empty())
        {
            std::size_t rowSize = static_cast<std::size_t>(m_size.x) * m_depth;

            for (std::size_t y = 0; y < m_size.y; ++y)
            {
                std::vector<BYTE>::iterator left = m_pixels.begin() + y * rowSize;
                std::vector<BYTE>::iterator right = m_pixels.begin() + (y + 1) * rowSize - m_depth;

                for (std::size_t x = 0; x < m_size.x / 2; ++x)
                {
                    std::swap_ranges(left, left + m_depth, right);

                    left += m_depth;
                    right -= m_depth;
                }
            }
        }
    }
}