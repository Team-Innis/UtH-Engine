#pragma once
#ifndef AFFECTOR_H_UTH
#define AFFECTOR_H_UTH

#include <functional>


namespace uth
{
    class Particle;
    class ParticleTemplate;

    class Affector
    {
    private:

        typedef std::function<void(Particle&, const ParticleTemplate&, float)> ParticleUpdateFunc;


    public:

        Affector();

        Affector(ParticleUpdateFunc func);

        virtual ~Affector(){};


        virtual void UpdateParticle(Particle& particle, const ParticleTemplate&, float dt);

        void SetUpdateFunc(ParticleUpdateFunc func);

    private:
     
        ParticleUpdateFunc m_func;

    };
}

#endif