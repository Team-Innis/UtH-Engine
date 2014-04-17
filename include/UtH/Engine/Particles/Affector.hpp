#pragma once
#ifndef AFFECTOR_H_UTH
#define AFFECTOR_H_UTH


namespace uth
{
    class Particle;

    class Affector
    {
    public:

        //virtual ~Affector();

        virtual void UpdateParticle(Particle& particle, float dt) = 0;

    };
}

#endif