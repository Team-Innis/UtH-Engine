#include "UtH/Engine/Scene.hpp"
#include <UtH/Engine/Sprite.hpp>

#include <UtH/Platform/Debug.hpp>
#include <Box2D/Dynamics/b2World.h>

using namespace uth;

Scene::Scene()
	: m_world(new b2World(b2Vec2(0.0f, GRAVITY)))
{

}

Scene::~Scene()
{

}


// Protected

Layer* Scene::CreateLayer(const int layerId, const bool adoptObjects)
{
	auto itr = m_layers.find(layerId);

    if (itr != m_layers.end())
    {
        WriteError("Layer with id#%d exists already. Returning it.", layerId);
        return itr->second.get();
    }

    Layer* ptr = new Layer(layerId, adoptObjects);
    m_layers[layerId] = std::unique_ptr<Layer, LayerDeleter>(ptr);

	return ptr;
}

bool uth::Scene::DeleteLayer(const int layerID)
{
    auto itr = m_layers.find(layerID);

    if (itr != m_layers.end())
    {
        m_layers.erase(itr);
        return true;
    }

    return false;
}

Layer* uth::Scene::GetLayer(const int layerID)
{
    auto itr = m_layers.find(layerID);

    if (itr != m_layers.end())
        return itr->second.get();

    return nullptr;
}

GameObject* Scene::AddGameObjectToLayer(const int layerId, GameObject* gameObject)
{
    auto itr = m_layers.find(layerId);

    if (itr != m_layers.end())
    {
        return itr->second->AddGameObject(gameObject);
    }

	return nullptr;
}

GameObject* Scene::RemoveGameObjectFromLayer(const int layerId, GameObject* gameObject, const bool deleteObject)
{
    auto itr = m_layers.find(layerId);

    if (itr != m_layers.end())
    {
        return itr->second->RemoveGameObject(gameObject, deleteObject);
    }

	return nullptr;
}

void uth::Scene::UpdateLayers(float dt, const int id)
{
    if (id < 0)
    {
        for (auto& i : m_layers)
            i.second->Update(dt);
    }
    else
    {
        auto itr = m_layers.find(id);

        if (itr != m_layers.end())
            itr->second->Update(dt);
    }
}

void uth::Scene::DrawLayers(RenderTarget& target, const int id)
{
    if (id < 0)
    {
        for (auto& i : m_layers)
            i.second->Draw(target);
    }
    else
    {
        auto itr = m_layers.find(id);

        if (itr != m_layers.end())
            itr->second->Draw(target);
    }
}