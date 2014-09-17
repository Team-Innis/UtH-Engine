#include <UtH/Engine/Layer.hpp>
#include <UtH/Engine/GameObject.hpp>


using namespace uth;

Layer::Layer(const int layerId, const bool adoptObjects)
	: m_gameObject(),
      transform(m_gameObject.transform),
      layerId(layerId),
      m_adopt(adoptObjects),
      m_active(true)
{

}

Layer::~Layer()
{
    if (m_adopt)
        Clear();
}


void uth::Layer::Clear()
{
    for (auto i : m_objects)
        delete i;

    m_objects.clear();
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

GameObject* uth::Layer::GetGameObject(const std::string& name)
{
    for (auto& i : m_objects)
    {
        if (i->GetName() == name)
            return i;
    }

    return nullptr;
}

bool uth::Layer::HasGameObject(GameObject* gameObject)
{
    return m_objects.find(gameObject) != m_objects.end();
}

GameObject* Layer::AddGameObject(GameObject* gameObject)
{
    if (gameObject)
    {
        m_objects.emplace(gameObject);

        // TODO: better solution
        assert(!gameObject->parent);
        gameObject->parent = &this->m_gameObject;
    }

	return gameObject;
}

GameObject* Layer::RemoveGameObject(GameObject* gameObject, const bool deleteObject)
{
    if (!gameObject)
        return nullptr;

	auto itr = m_objects.find(gameObject);

    if (itr != m_objects.end())
    {
        GameObject* ptr = *itr;
        m_objects.erase(itr);

        if (deleteObject)
        {
            delete ptr;
            return nullptr;
        }

        return ptr;
    }

	return nullptr;
}

void Layer::Update(float dt)
{
    if (IsActive())
    {
        for (auto& i : m_objects)
        {
            if (i->IsActive())
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
