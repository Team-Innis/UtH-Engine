#pragma once
#ifndef PARTICLE_H_UTH
#define PARTICLE_H_UTH

#include <UtH/Engine/Transform.hpp>


namespace uth
{

    class Particle : public Transform
    {
    public:

        Particle(const Transform& transform)
            : Transform(transform)
        {}

        float lifetime;
        pmath::Vec2 direction;
        pmath::Vec4 color;

    };
}

#endif