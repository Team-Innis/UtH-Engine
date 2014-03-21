#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Layer.hpp>
#include <Box2D/Box2D.h>

#include <vector>

namespace uth
{
	const float GRAVITY = 10.f;

	class Scene
	{
	public:
		friend class SceneManager;
		Scene();
		~Scene();

		virtual bool Init() = 0;
		virtual bool DeInit() = 0;

		virtual bool Update(double dt) = 0;
		virtual bool Draw() = 0;	

	protected:
		//LAYERS
		bool CreateLayer(const char* layerName);
		bool CreateLayer(const int layerId);
		bool CreateLayer(const char* layerName, const int layerId);
		void SetLayerActive(const char* layerName, bool active);
		void SetLayerActive(const int layerId, bool active);
		bool AddGameObjectToLayer(const char* layerName, GameObject* gameObject);
		bool AddGameObjectToLayer(int layerId, GameObject* gameObject);
		bool RemoveGameObjectFromLayer(const char* layerName, GameObject* gameObject);
		bool RemoveGameObjectFromLayer(int LayerId, GameObject* gameObject);

		std::vector<Layer*> layers;
		int layersCount;

		GameObject layer;

		b2World world;
	};
}

#endif
