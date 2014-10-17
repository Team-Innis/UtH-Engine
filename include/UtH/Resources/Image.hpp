#pragma once
#ifndef IMAGE_H_UTH
#define IMAGE_H_UTH


#include <pmath/Vector2.hpp>
#include <pmath/Vector4.hpp>
#include <UtH/Platform/Typedefs.hpp>
#include <string>
#include <vector>
#include <UtH/Resources/Resource.hpp>


namespace uth
{

	class Image : public Resource
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

        pmath::Vec4 GetPixel(unsigned int x, unsigned int y);

        void flipVertical();

        void flipHorizontal();


    private:

        Image();

        ~Image();


        bool LoadFromFile(const std::string& filePath);

		bool Unload();

        // Member data

        pmath::Vec2 m_size;
        std::vector<BYTE> m_pixels;
        BYTE m_depth;

    };
}

#endif