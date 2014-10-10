#include <UtH/Engine/Particles/ParticleSystem.hpp>
#include <UtH/Core/Randomizer.hpp>
#include <algorithm>
#include <iostream>

using namespace uth;


ParticleSystem::ParticleSystem(const size_t reserve)
	: GameObject(),
	  m_batch(false),
      m_emitAmount(1, 1),
      m_emitFreq(0.f, 1.f),
      m_emitTimer(0.f),
      m_emitTimeLimit(0.f),
      m_currentParticle(0u),
      m_autoEmit(false),
      m_update(false)
{
    m_particles.reserve(reserve);
	transform.setSize(1,1);
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

        for (auto& i : m_affectors)
		    i->InitParticle(p, m_template);

        p.lifetime = 0;
        m_batch.AddSprite(&p);
	}
}

void uth::ParticleSystem::WarmUp(const float time, const float step)
{
    float currTime = 0.f;

    while ((currTime += step) <= time)
    {
        update(step);
    }
}

bool ParticleSystem::ReadyToEmit() const
{
    bool ready = m_emitTimer >= m_emitTimeLimit;
    
    if (ready)
    {
        m_emitTimer -= m_emitTimeLimit;
        m_emitTimeLimit = Randomizer::GetFloat(m_emitFreq.x, m_emitFreq.y);
    }

    return ready;
}

void ParticleSystem::SetEmitProperties(const bool autoEmit, const float min, const float max, const int minAmount, const int maxAmount)
{
    m_autoEmit = autoEmit;

    m_emitFreq.x = min;
    m_emitFreq.y = max;

    m_emitAmount.x = minAmount;
    m_emitAmount.y = maxAmount;
}

void ParticleSystem::AddAffector(Affector* affector)
{
    if (affector)
    {
        m_affectors.emplace_back(affector);
        affector->m_system = this;
    }
}

void ParticleSystem::SetTemplate(const ParticleTemplate& pTemplate)
{
	m_template = pTemplate;
	m_batch.SetTexture(m_template.m_texture);
	transform.setSize(m_template.m_texture->GetSize());
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
    m_emitTimer += dt;

    if (m_autoEmit && ReadyToEmit())
    {
        Emit(std::max(0, Randomizer::GetInt(m_emitAmount.x, m_emitAmount.y)));
    }

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
            return (maxLifetime >= 0.f ? ((particle.lifetime += deltaTime) >= maxLifetime) : (particle.lifetime > 0.f));
		}
	};

	const unsigned int size = m_particles.size();

	m_particles.erase(std::remove_if(m_particles.begin(), m_particles.end(), 
		Eraser(m_template.lifetime, dt)), m_particles.end());

	if (m_update || size > m_particles.size())
	{
        m_update = false;
		m_batch.Clear();
		for (auto& i : m_particles)
        {
			m_batch.AddSprite(&i, "", i.color);
		}
	}

	for (auto& a : m_affectors)
	{
        a->Update(dt);
		for (auto& p : m_particles)
		{
			a->UpdateParticle(p, m_template, dt);
            ++m_currentParticle;
		}
	}
    m_currentParticle = 0;
}

void ParticleSystem::draw(RenderTarget& target)
{
	m_batch.Draw(target);
}

unsigned int ParticleSystem::GetCurrentParticleNumber() const
{
    return m_currentParticle;
}

unsigned int ParticleSystem::GetParticleAmount() const
{
    return m_particles.size();
}

size_t ParticleSystem::GetParticleLimit() const
{
    return m_particles.capacity();
}