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
    public:

        Affector();

        Affector(std::function<void(Particle&, ParticleTemplate&, float)> func);

        virtual ~Affector(){};



        virtual void UpdateParticle(Particle& particle, ParticleTemplate&, float dt);

        void SetUpdateFunc(std::function<void(Particle&, ParticleTemplate&, float)> func);

    private:
        
        std::function<void(Particle&, ParticleTemplate&, float)> m_func;

    };
}

#endif