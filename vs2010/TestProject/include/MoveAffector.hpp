#pragma once
#ifndef MOVEAFFECTOR_H
#define MOVEAFFECTOR_H

#include <UtH/Engine/Particles/Affector.hpp>
#include <UtH/Engine/Particles/Particle.hpp>


namespace uth
{

    class MoveAffector : public Affector
    {
    public:

        void UpdateParticle(Particle& particle, float dt)
        {
            //particle.direction *= 0.95f;
            particle.transform.Move(particle.direction);
            particle.transform.Rotate(5);
        }

    };
}

#endif