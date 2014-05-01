#include <UtH/Engine/Particles/Affector.hpp>

using namespace uth;



Affector::Affector()
    : m_func([](Particle&, ParticleTemplate&, float){})
{

}

Affector::Affector(std::function<void(Particle&, ParticleTemplate&, float)> func)
    : m_func(func)
{
    
}

void Affector::UpdateParticle(Particle& particle, ParticleTemplate& pTemplate, float dt)
{
    m_func(particle, pTemplate, dt);
}

void Affector::SetUpdateFunc(std::function<void(Particle&, ParticleTemplate&, float)> func)
{
    m_func = func;
}