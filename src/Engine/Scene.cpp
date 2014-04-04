#include "UtH/Engine/Scene.hpp"
#include <UtH/Engine/Sprite.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

bool sortFunc(Layer* a,Layer* b)
{
	return a->GetLayerId() < b->GetLayerId();
}

Scene::Scene()
	: layersCount(0),
	  world(b2Vec2(0.0f, GRAVITY))
{ }

Scene::~Scene()
{
	for(size_t i = 0; i < layers.size(); i++)
		delete layers.at(i);
}


// Protected

bool Scene::CreateLayer(const int layerId)
{
	for(size_t i = 0; i < layers.size(); i++)
	{
		if(layerId == layers.at(i)->GetLayerId())
		{
			WriteError("Layer with id#%d exists already.\nProceeding to create new LayerID", layerId);
			CreateLayer(createLayerWithAnotherID());
			return true;
		}
	}

	layers.push_back(new Layer(layerId));
	
	if(layers.size() < layersCount)
		return false;

	layersCount++;
	arrangeLayers();
	return true;
}

bool Scene::CreateLayer(const char* layerName, const int layerId)
{
	for(size_t i = 0; i < layers.size(); i++)
	{
		if(layerId == layers.at(i)->GetLayerId())
		{
			WriteError("Layer with ID#%d exists already.\nProceeding to create new layerID", layerId);
			CreateLayer(layerName, createLayerWithAnotherID());
			return true;
		}
		if(layerName == layers.at(i)->GetLayerName())
		{
			WriteLog("\n*******WARNING*******\n"
				"Layer with name '%s' already exists.\n"
				"Use layer ID(%d) to remove gameobjects.\n"
				"*********************\n\n", layerName, layerId);
		}
	}

	layers.push_back(new Layer(layerName, layerId));
	
	if(layers.size() < layersCount)
		return false;

	arrangeLayers();
	layersCount++;
	return true;
}

void Scene::SetLayerActive(const char* layerName,bool active)
{
	for(size_t i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerName() == layerName)
		{
			layers.at(i)->SetObjectsActive(active);
		}
	}
}

void Scene::SetLayerActive(const int layerId,bool active)
{
	for(size_t i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerId() == layerId)
		{
			layers.at(i)->SetObjectsActive(active);
		}
	}
}

bool Scene::AddGameObjectToLayer(const char* layerName, GameObject* gameObject)
{
	for(size_t i = 0; i < layers.size(); i++)
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
	for(size_t i = 0; i < layers.size(); i++)
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
	for(size_t i = 0; i < layers.size(); i++)
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
	for(size_t i = 0; i < layers.size(); i++)
	{
		if(layers.at(i)->GetLayerId() == layerId)
		{
			layers.at(i)->RemoveGameObject(gameObject);
			return true;
		}
	}

	return false;
}


// Private

int Scene::createLayerWithAnotherID()
{
	bool newID = true;

	for(int i = 0; i < 9; i++)
	{
		for(size_t j = 0; j < layers.size(); j++)
		{
			if(layers.at(j)->GetLayerId() == i)
				newID = false;
		}
		if(newID)
		{
			WriteLog("Creating layer with id#%d\n", i);
			return i;
		}
		newID = true;
	}
	return -1;
}

void Scene::arrangeLayers()
{
	std::sort(layers.begin(),layers.end(),sortFunc);
}