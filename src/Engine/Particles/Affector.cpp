#include <UtH/Engine/Particles/Affector.hpp>

using namespace uth;


Affector::Affector()
	: m_initFunc(),
      m_puFunc(),
      m_uFunc()
{

}


void Affector::InitParticle(Particle& particle, const ParticleTemplate& pt)
{
    if (m_initFunc)
        m_initFunc(particle, pt);
}

void uth::Affector::Update(float dt)
{
    if (m_uFunc)
        m_uFunc(dt);
}

void Affector::UpdateParticle(Particle& particle, const ParticleTemplate& pTemplate, float dt)
{
    if (m_puFunc)
        m_puFunc(particle, pTemplate, dt);
}

void uth::Affector::SetUpdateFunc(UpdateFunc func)
{
    m_uFunc = func;
}

void Affector::SetParticleUpdateFunc(ParticleUpdateFunc func)
{
    m_puFunc = func;
}

void uth::Affector::SetParticleInitFunc(InitFunc func)
{
    m_initFunc = func;
}

const ParticleSystem* Affector::GetSystem() const
{
    return m_system;
}