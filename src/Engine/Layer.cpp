#include <UtH/Engine/Layer.hpp>

using namespace uth;

Layer::Layer()
	: layerName(""),
	  objectCount(0),
	  layerId(0)
{
}

Layer::Layer(const int layerId)
	: layerName(""),
	  objectCount(0),
	  layerId(layerId)
{
}

Layer::Layer(const char* layerName, const int layerId)
	: layerName(layerName),
	  objectCount(0),
	  layerId(layerId)
{
}

Layer::~Layer()
{
	m_objects.clear();
}

void Layer::SetLayerName(const char* layerName)
{
	this->layerName = layerName;
}

const char* Layer::GetLayerName()
{
	return layerName;
}

const int Layer::GetLayerId()
{
	return layerId;
}

bool Layer::AddGameObject(GameObject* gameObject)
{
	m_objects.push_back(gameObject);

	if(m_objects.size() < objectCount)
		return false;
	
	objectCount++;
	return true;
}

bool Layer::RemoveGameObject(GameObject* gameObject)
{
	std::vector<GameObject*>::iterator it;
	for(it = m_objects.begin(); it != m_objects.end(); ++it)
	{
		if((*it) == gameObject)
		{
			m_objects.erase(it);
			objectCount--;
			return true;
		}
	}
	return false;
}

void Layer::Update(float dt)
{
	for(size_t i = 0; i < m_objects.size(); ++i)
	{
		m_objects.at(i)->Update(dt);
	}

	UpdateTransform();
}

void Layer::Draw(RenderTarget& target)
{
	for(size_t i = 0; i < m_objects.size(); ++i)
	{
		if(m_objects.at(i)->transform.IsActive())
			m_objects.at(i)->Draw(target);
	}
}

void Layer::SetObjectsActive(bool value)
{
	for(size_t i = 0; i < m_objects.size(); ++i)
	{
		m_objects.at(i)->transform.SetActive(value);
		//m_objects.at(i)->transform.SetDrawable(value);
	}
}

void Layer::UpdateTransform()
{
	
	for(size_t i = 0; i < m_objects.size(); ++i)
	{
		m_objects.at(i)->transform.AddTransform(transform.GetTransform());
		/*
		m_objects.at(i)->transform.SetTransform(transform.GetTransform() *
			m_objects.at(i)->transform.GetTransform());
			*/
	}
	
}