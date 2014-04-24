#include <UtH/Engine/Particles/Affector.hpp>

using namespace uth;



Affector::Affector()
    : m_func([](Particle&, float){})
{

}

Affector::Affector(std::function<void(Particle&, float)> func)
    : m_func(func)
{
    
}

void Affector::UpdateParticle(Particle& particle, float dt)
{
    m_func(particle, dt);
}

void Affector::SetUpdateFunc(std::function<void(Particle&, float)> func)
{
    m_func = func;
}