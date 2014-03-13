#pragma once
#ifndef VERTEX_H_UTH
#define VERTEX_H_UTH

#include <UtH\Math\Vector2.hpp>
#include <UtH\Math\Vector3.hpp>


namespace uth
{
    class Vertex
    {
    public:

        Vertex();

        Vertex(const umath::vector3& pos, const umath::vector2& uv)
            : position(pos),
              texCoords(uv)
        {}


        umath::vector3 position;
        umath::vector2 texCoords;

    };
}
#endif