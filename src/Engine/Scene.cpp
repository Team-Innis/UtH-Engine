#include "UtH/Engine/Scene.hpp"
#include <UtH/Engine/Sprite.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

Scene::Scene()
	: layersCount(0),
	  world(b2Vec2(0.0f, GRAVITY))
{ }

Scene::~Scene()
{
	for(int i = 0; i < layers.size(); i++)
		delete layers.at(i);
}

bool Scene::CreateLayer(const char* layerName)
{
	layers.push_back(new Layer(layerName, layersCount));
	
	if(layers.size() < layersCount)
		return false;

	layersCount++;
	return true;
}

bool Scene::CreateLayer(const int layerId)
{
	layers.push_back(new Layer(layerId));
	
	if(layers.size() < layersCount)
		return false;

	layersCount++;
	return true;
}

bool Scene::CreateLayer(const char* layerName, const int layerId)
{
	layers.push_back(new Layer(layerName, layerId));
	
	if(layers.size() < layersCount)
		return false;

	layersCount++;
	return true;
}

void Scene::SetLayerActive(const char* layerName,bool active)
{
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerName() == layerName)
		{
			layers.at(i)->SetObjectsActive(active);
		}
	}
}

void Scene::SetLayerActive(const int layerId,bool active)
{
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerId() == layerId)
		{
			layers.at(i)->SetObjectsActive(active);
		}
	}
}

bool Scene::AddGameObjectToLayer(const char* layerName, GameObject* gameObject)
{
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerName() == layerName)
		{
			layers.at(i)->AddGameObject(gameObject);
			return true;
		}
	}

	return false;
}

bool Scene::AddGameObjectToLayer(int layerId, GameObject* gameObject)
{
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerId() == layerId)
		{
			layers.at(i)->AddGameObject(gameObject);
			return true;
		}
	}

	return false;
}

bool Scene::RemoveGameObjectFromLayer(const char* layerName, GameObject* gameObject)
{
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerName() == layerName)
		{
			layers.at(i)->RemoveGameObject(gameObject);
			return true;
		}
	}

	return false;
}

bool Scene::RemoveGameObjectFromLayer(int layerId, GameObject* gameObject)
{
	for(int i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerId() == layerId)
		{
			layers.at(i)->RemoveGameObject(gameObject);
			return true;
		}
	}

	return false;
}