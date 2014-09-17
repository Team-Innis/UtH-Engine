#pragma once
#ifndef PARTICLESYSTEM_H_UTH
#define PARTICLESYSTEM_H_UTH

#include <UtH/Platform/HiResTimer.hpp>

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/SpriteBatch.hpp>

#include <UtH/Engine/Particles/ParticleTemplate.hpp>
#include <UtH/Engine/Particles/Affector.hpp>
#include <UtH/Engine/Particles/Particle.hpp>

namespace uth
{

    class ParticleSystem : public GameObject
    {
    public:

        ParticleSystem(const size_t reserve);

        ~ParticleSystem(){};


        void Emit(const unsigned int amount);

        void WarmUp(const float time, const float step = 1.f / 60.f);

        bool ReadyToEmit() const;

        void SetEmitProperties(const bool autoEmit, const float min = 0.f, const float max = 1.f, const int minAmount = 1, const int maxAmount = 1);

        void AddAffector(Affector* affector);

        void SetTemplate(const ParticleTemplate& pTemplate);

        void Clear(const bool particles = true, const bool affectors = true);

        unsigned int GetCurrentParticleNumber() const;

        unsigned int GetParticleAmount() const;

        size_t GetParticleLimit() const;

        void RaiseUpdateFlag();

    private:
     
        void update(float dt);
        void draw(RenderTarget& target);

        ParticleTemplate m_template;
        SpriteBatch m_batch;

        std::vector<std::unique_ptr<Affector>> m_affectors;
        std::vector<Particle> m_particles;

        pmath::Vec2i m_emitAmount;
        pmath::Vec2 m_emitFreq;
        mutable float m_emitTimer;
        mutable float m_emitTimeLimit;
        unsigned int m_currentParticle;
        bool m_autoEmit;
        bool m_update;

    };

}

#endif