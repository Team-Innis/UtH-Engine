#pragma once
#ifndef AFFECTOR_H_UTH
#define AFFECTOR_H_UTH

#include <functional>


namespace uth
{
    class Particle;
    class ParticleTemplate;
    class ParticleSystem;

    class Affector
    {
    private:

        friend class ParticleSystem;

        typedef std::function<void(Particle&, const ParticleTemplate&, float)> ParticleUpdateFunc;
        typedef std::function<void(float)> UpdateFunc;


    public:

        Affector();

        Affector(ParticleUpdateFunc particleUpdateFunc, UpdateFunc updateFunc);

        virtual ~Affector(){};


        virtual void Update(float dt);

        virtual void UpdateParticle(Particle& particle, const ParticleTemplate& pt, float dt);

        void SetParticleUpdateFunc(ParticleUpdateFunc func);

        void SetUpdateFunc(UpdateFunc func);

        const ParticleSystem* GetSystem() const;

    private:
     
        ParticleUpdateFunc m_puFunc;
        UpdateFunc m_uFunc;
        ParticleSystem* m_system;

    };
}

#endif