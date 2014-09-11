#include <UtH/Engine/Particles/ParticleSystem.hpp>
#include <UtH/Core/Randomizer.hpp>
#include <algorithm>
#include <iostream>

using namespace uth;


ParticleSystem::ParticleSystem(const size_t reserve)
	: GameObject(),
	  m_batch(false)
{
    m_particles.reserve(reserve);
}

void ParticleSystem::Emit(const unsigned int amount)
{
	for (size_t i = 0; i < amount; ++i)
	{
        if (m_particles.size() < m_particles.capacity())
            m_particles.emplace_back(this->transform);
        else
            return;

        auto& p = m_particles.back();
	    p.color = m_template.color;

		m_template.m_pInitFunc(p, m_template);

        p.lifetime = 0;
        m_batch.AddSprite(&p);
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
		Eraser(float maxLT, float delta)
			: maxLifetime(maxLT),
              deltaTime(delta)
		{}

		float maxLifetime;
        float deltaTime;

		bool operator()(Particle& particle)
		{
			return (particle.lifetime += deltaTime) >= maxLifetime;
		}
	};

	const unsigned int size = m_particles.size();

	m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(), Eraser(m_template.lifetime, dt)), m_particles.end());

	if (size > m_particles.size())
	//if (true)
	{
		m_batch.Clear();
		for (auto& i : m_particles)
        {
			m_batch.AddSprite(&i, "", i.color);
		}
	}

	for (auto& p : m_particles)
	{
		for (auto& a : m_affectors)
		{
			a->UpdateParticle(p, m_template, dt);
		}
	}
}

void ParticleSystem::draw(RenderTarget& target)
{
	m_batch.Draw(target);
}