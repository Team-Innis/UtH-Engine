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

        typedef std::function<void(Particle&, const ParticleTemplate&)> InitFunc;
        typedef std::function<void(Particle&, const ParticleTemplate&, float)> ParticleUpdateFunc;
        typedef std::function<void(float)> UpdateFunc;


    public:

        Affector();

        virtual ~Affector(){};


        virtual void InitParticle(Particle& particle, const ParticleTemplate& pt);

        virtual void Update(float dt);

        virtual void UpdateParticle(Particle& particle, const ParticleTemplate& pt, float dt);

        void SetParticleInitFunc(InitFunc func);

        void SetParticleUpdateFunc(ParticleUpdateFunc func);

        void SetUpdateFunc(UpdateFunc func);

        const ParticleSystem* GetSystem() const;

    private:
     
        InitFunc m_initFunc;
        ParticleUpdateFunc m_puFunc;
        UpdateFunc m_uFunc;
        ParticleSystem* m_system;

    };
}

#endif