#include <UtH/Engine/Layer.hpp>
#include <UtH/Engine/GameObject.hpp>


using namespace uth;

Layer::Layer(const int layerId, const bool adoptObjects)
	: layerId(layerId),
      m_adopt(adoptObjects),
      m_active(true)
{

}

Layer::~Layer()
{
    if (m_adopt)
    {
        for (auto i : m_objects)
            delete i;
    }
}


int Layer::GetLayerId() const
{
	return layerId;
}

void uth::Layer::SetActive(const bool active)
{
    m_active = active;
}

bool uth::Layer::IsActive() const
{
    return m_active;
}

bool Layer::AddGameObject(GameObject* gameObject)
{
	m_objects.emplace(gameObject);

	return true;
}

GameObject* Layer::RemoveGameObject(GameObject* gameObject)
{
	auto itr = m_objects.find(gameObject);

    if (itr != m_objects.end())
        return *itr;

	return nullptr;
}

void Layer::Update(float dt)
{
    if (IsActive())
    {
        for (auto& i : m_objects)
        {
            i->Update(dt);
        }
    }
}

void Layer::Draw(RenderTarget& target)
{
    if (IsActive())
    {
        for (auto& i : m_objects)
        {
            if (i->IsActive())
                i->Draw(target);
        }
    }
}