#pragma once
#ifndef IMAGE_H_UTH
#define IMAGE_H_UTH


#include <UtH\Math\Vector2.hpp>
#include <UtH\Math\Vector4.hpp>
#include <UtH\Platform\Typedefs.hpp>
#include <string>


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


        const umath::vector2& GetSize() const;


        umath::vector4 GetPixel(unsigned int x, unsigned int y) const;




    private:

        umath::vector2 m_size;
        BYTE* m_pixels;
        BYTE m_depth;

    };

}



#endif