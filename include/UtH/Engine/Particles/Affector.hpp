#pragma once
#ifndef AFFECTOR_H_UTH
#define AFFECTOR_H_UTH

#include <functional>


namespace uth
{
    class Particle;

    class Affector
    {
    public:

        Affector();

        Affector(std::function<void(Particle&, float)> func);

        virtual ~Affector(){};



        virtual void UpdateParticle(Particle& particle, float dt);

        void SetUpdateFunc(std::function<void(Particle&, float)> func);

    private:
        
        std::function<void(Particle&, float)> m_func;

    };
}

#endif