#include <UtH/Engine/Particles/ParticleSystem.hpp>
#include <UtH/Engine/Randomizer.hpp>
#include <UtH/Engine/SceneManager.hpp>
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

void ParticleSystem::RaiseUpdateFlag()
{
    m_update = true;
}

rapidjson::Value ParticleSystem::save(rapidjson::MemoryPoolAllocator<>& alloc) const
{
    namespace rj = rapidjson;

    rapidjson::Value val = GameObject::save(alloc);

    val.AddMember(rj::StringRef("particleLimit"), m_particles.capacity(), alloc)
       .AddMember(rj::StringRef("properties"), rj::kArrayType, alloc);

    val["properties"].PushBack(m_emitAmount.x, alloc)
                     .PushBack(m_emitAmount.y, alloc)
                     .PushBack(m_emitFreq.x, alloc)
                     .PushBack(m_emitFreq.y, alloc)
                     .PushBack(m_emitTimer, alloc)
                     .PushBack(m_emitTimeLimit, alloc)
                     .PushBack(m_autoEmit, alloc);

    // Template
    {
        rj::Value& tempVal = val.AddMember(rj::StringRef("template"), rj::kObjectType, alloc)["template"];

        rj::Value& colVal = tempVal.AddMember(rj::StringRef("color"), rj::kArrayType, alloc)["color"];
        colVal.PushBack(m_template.color.r, alloc)
              .PushBack(m_template.color.g, alloc)
              .PushBack(m_template.color.b, alloc)
              .PushBack(m_template.color.a, alloc);

        tempVal.AddMember(rj::StringRef("lifetime"), m_template.lifetime, alloc);
        tempVal.AddMember(rj::StringRef("minSpeed"), m_template.minSpeed, alloc);
        tempVal.AddMember(rj::StringRef("maxSpeed"), m_template.maxSpeed, alloc);

        if (m_template.m_texture)
            tempVal.AddMember(rj::StringRef("texture"), rj::Value(uthRS.FilePath(m_template.m_texture, ResourceManager::Textures).c_str(), alloc), alloc);

        rj::Value& tcVal = tempVal.AddMember(rj::StringRef("texCoords"), rj::kArrayType, alloc)["texCoords"];
        tcVal.PushBack(m_template.m_texCoords.position.x, alloc)
             .PushBack(m_template.m_texCoords.position.y, alloc)
             .PushBack(m_template.m_texCoords.size.x, alloc)
             .PushBack(m_template.m_texCoords.size.y, alloc);
    }

    // Affectors
    if (!m_affectors.empty())
    {
        rj::Value& aArray = val.AddMember(rj::StringRef("affectors"), rj::kArrayType, alloc)["affectors"];

        for (auto& i : m_affectors)
        {
            rj::Value aff(i->save(alloc));

            aff.AddMember(rj::StringRef("identifier"), rj::StringRef(typeid(*i).raw_name()), alloc);

            aArray.PushBack(aff, alloc);
        }
    }

    return val;
}

bool uth::ParticleSystem::load(const rapidjson::Value& doc)
{
    namespace rj = rapidjson;

    if (!GameObject::load(doc))
        return false;

    const rj::Value& props = doc["properties"];

    m_emitAmount.x = props[0u].GetInt();
    m_emitAmount.y = props[1].GetInt();
    m_emitFreq.x = props[2].GetDouble();
    m_emitFreq.y = props[3].GetDouble();
    m_emitTimer = props[4].GetDouble();
    m_emitTimeLimit = props[5].GetDouble();
    m_autoEmit = props[6].GetBool();

    // Template
    {
        const rj::Value& tempVal = doc["template"];

        const rj::Value& colVal = tempVal["color"];
        m_template.color.r = colVal[0u].GetDouble();
        m_template.color.g = colVal[1].GetDouble();
        m_template.color.b = colVal[2].GetDouble();
        m_template.color.a = colVal[3].GetDouble();

        m_template.lifetime = tempVal["lifetime"].GetDouble();
        m_template.minSpeed = tempVal["minSpeed"].GetDouble();
        m_template.maxSpeed = tempVal["maxSpeed"].GetDouble();

        if (tempVal.HasMember("texture"))
            m_template.m_texture = uthRS.LoadTexture(tempVal["texture"].GetString());

        const rj::Value& tcVal = tempVal["texCoords"];
        m_template.m_texCoords.position.x = tcVal[0u].GetDouble();
        m_template.m_texCoords.position.y = tcVal[1].GetDouble();
        m_template.m_texCoords.size.x = tcVal[2].GetDouble();
        m_template.m_texCoords.size.y = tcVal[3].GetDouble();
    }

    // Affectors
    if (doc.HasMember("affectors") && doc["affectors"].IsArray())
    {
        const rj::Value& aArray = doc["affectors"];

        for (auto itr = aArray.Begin(); itr != aArray.End(); ++itr)
        {
            std::unique_ptr<Affector> ptr(static_cast<Affector*>(uthSceneM.GetSaveable(*itr)));

            if (!ptr && !ptr->load(*itr))
                continue;

            AddAffector(ptr.release());
        }
    }

    return true;
}