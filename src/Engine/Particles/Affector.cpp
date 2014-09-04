#include <UtH/Engine/Particles/Affector.hpp>

using namespace uth;



Affector::Affector()
	: m_func()
{
}

Affector::Affector(ParticleUpdateFunc func)
	: m_func(func)
{
}

void Affector::UpdateParticle(Particle& particle, const ParticleTemplate& pTemplate, float dt)
{
    if (m_func)
	    m_func(particle, pTemplate, dt);
}

void Affector::SetUpdateFunc(ParticleUpdateFunc func)
{
	m_func = func;
}