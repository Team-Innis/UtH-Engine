#pragma once
#ifndef VERTEX_H_UTH
#define VERTEX_H_UTH

#include <pmath/Vector.hpp>

namespace uth
{
    class Vertex
    {
    public:

        Vertex();

        Vertex(const pmath::Vec3& pos, const pmath::Vec2& uv,
			const pmath::Vec4& col = pmath::Vec4(1, 1, 1, 1))
            : position(pos),
              texCoords(uv),
			  color(col)
        {}


        pmath::Vec3 position;
        pmath::Vec2 texCoords;
		pmath::Vec4 color;

    };
}
#endif