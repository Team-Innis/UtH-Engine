#pragma once
#ifndef IMAGE_H_UTH
#define IMAGE_H_UTH


#include <pmath/Vector2.hpp>
#include <pmath/Vector4.hpp>
#include <UtH/Platform/Typedefs.hpp>
#include <string>
#include <vector>


namespace uth
{

    class Image
    {

        friend class Texture;

    public:

        Image();

        Image(const std::string& filePath);

        ~Image();


        bool LoadFromFile(const std::string& filePath);

        const pmath::Vec2& GetSize() const;

		BYTE GetDepth() const;

        pmath::Vec4 GetPixel(unsigned int x, unsigned int y) const;

        void flipVertical();

        void flipHorizontal();


    private:

        pmath::Vec2 m_size;
        std::vector<BYTE> m_pixels;
        BYTE m_depth;

    };
}

#endif