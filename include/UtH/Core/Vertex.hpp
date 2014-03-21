#pragma once
#ifndef VERTEX_H_UTH
#define VERTEX_H_UTH

#include <UtH/Math/Vector.hpp>

namespace uth
{
    class Vertex
    {
    public:

        Vertex();

        Vertex(const umath::vector3& pos, const umath::vector2& uv,
			const umath::vector4& col = umath::vector4(1, 1, 1, 1))
            : position(pos),
              texCoords(uv),
			  color(col)
        {}


        umath::vector3 position;
        umath::vector2 texCoords;
		umath::vector4 color;

    };
}
#endif