#pragma once
#ifndef PARTICLE_H_UTH
#define PARTICLE_H_UTH

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/HiResTimer.hpp>


namespace uth
{

    class Particle : public GameObject
    {
    public:

        Timer lifetime;
        umath::vector2 direction;

    };
}

#endif