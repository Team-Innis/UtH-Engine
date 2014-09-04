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
        umath::vector2 direction;
        umath::vector4 color;

    };
}

#endif