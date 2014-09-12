#include <UtH/Engine/Particles/Affector.hpp>

using namespace uth;



Affector::Affector()
	: m_puFunc(),
      m_uFunc()
{

}

Affector::Affector(ParticleUpdateFunc func, UpdateFunc uFunc)
    : m_puFunc(func),
      m_uFunc(uFunc)
{

}

void uth::Affector::Update(float dt)
{
    if (m_uFunc)
        m_uFunc(dt);
}

void uth::Affector::SetUpdateFunc(UpdateFunc func)
{
    m_uFunc = func;
}

const ParticleSystem* Affector::GetSystem() const
{
    return m_system;
}

void Affector::UpdateParticle(Particle& particle, const ParticleTemplate& pTemplate, float dt)
{
    if (m_puFunc)
	    m_puFunc(particle, pTemplate, dt);
}

void Affector::SetParticleUpdateFunc(ParticleUpdateFunc func)
{
	m_puFunc = func;
}
