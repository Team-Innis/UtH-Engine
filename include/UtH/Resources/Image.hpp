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
    private:

        struct Deleter
        {
            void operator()(Image* file) const
            {
                delete file;
            }
        };

        friend class Texture;
        friend class ResourceManager;

    public:

        const pmath::Vec2& GetSize() const;

		BYTE GetDepth() const;

        pmath::Vec4 GetPixel(unsigned int x, unsigned int y) const;

        void flipVertical();

        void flipHorizontal();


    private:

        Image();

        ~Image();


        bool LoadFromFile(const std::string& filePath);


        // Member data

        pmath::Vec2 m_size;
        std::vector<BYTE> m_pixels;
        BYTE m_depth;

    };
}

#endif