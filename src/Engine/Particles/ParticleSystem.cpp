#include <UtH/Engine/Particles/ParticleSystem.hpp>
#include <UtH/Core/Randomizer.hpp>
#include <algorithm>

using namespace uth;


ParticleSystem::ParticleSystem()
    : GameObject(),
      m_batch(false)
{
    
}

void ParticleSystem::Emit(const unsigned int amount)
{
    Particle p;
    p.transform = this->transform;
    p.color = m_template.color;

    for (unsigned int i = 0; i < amount; ++i)
    {
        m_template.m_pInitFunc(p, m_template);

        AddParticles(1, p);
    }
}



void ParticleSystem::AddAffector(Affector* affector)
{
    m_affectors.emplace_back(affector);
}

void ParticleSystem::SetTemplate(const ParticleTemplate& pTemplate)
{
    m_template = pTemplate;
    m_batch.SetTexture(m_template.m_texture);
}

void ParticleSystem::Clear(const bool particles, const bool affectors)
{
    if (particles)
    {
        m_particles.clear();
        m_batch.Clear();
    }
    if (affectors)
        m_affectors.clear();
}

void ParticleSystem::update(float dt)
{
    struct Eraser
    {
        Eraser(double maxLT)
            : maxLifetime(maxLT)
        {}

        double maxLifetime;

        bool operator()(const std::unique_ptr<Particle>& particle)
        {
            return particle.get()->lifetime.CurTime() >= maxLifetime;
        }
    };

    const unsigned int size = m_particles.size();

    m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(), Eraser(m_template.lifetime)), m_particles.end());

    //if (size > m_particles.size())
    if (true)
    {
        m_batch.Clear();
        for (auto itr = m_particles.begin(); itr != m_particles.end(); ++itr)
        {
            m_batch.AddSprite(itr->get(), "", itr->get()->color);
        }
    }

    for (auto itr = m_particles.begin(); itr != m_particles.end(); ++itr)
    {
        for (auto itr2 = m_affectors.begin(); itr2 != m_affectors.end(); ++itr2)
        {
            itr2->get()->UpdateParticle(*itr->get(), m_template, dt);
        }
    }
}

void ParticleSystem::draw(RenderTarget& target)
{
    m_batch.Draw(target);
}

void ParticleSystem::AddParticles(const unsigned int amount, Particle& particle)
{
    particle.lifetime.Reset();

    for (unsigned int i = 0; i < amount; ++i)
    {
        m_particles.emplace_back(new Particle(particle));
        m_batch.AddSprite(m_particles.back().get());
    }
}