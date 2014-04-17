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

        virtual void UpdateParticle(Particle& particle, float dt){Update(particle, dt);}

        void setUpdateFunc(void (*UpdateFunc)(Particle& particle, float dt))
        {
            Update = UpdateFunc;
        }

    private:
        void (*Update)(Particle& particle, float dt);

    };
}

#endif