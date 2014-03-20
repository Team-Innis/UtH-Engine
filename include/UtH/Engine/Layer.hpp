#pragma once
#ifndef LAYER_H_UTH
#define LAYER_H_UTH

#include <UtH/Engine/GameObject.hpp>

#include <vector>

namespace uth
{
	class Layer
	{
	public:
		Layer();
		Layer(const int layerId);
		Layer(const char* layerName, const int layerId);
		~Layer();

		void SetLayerName(const char* layerName);
		const char* GetLayerName();

		void SetLayerId(const int layerId);
		const int GetLayerId();

		bool AddGameObject(GameObject* gameObject);
		bool RemoveGameObject(GameObject* gameObject);

		void Draw(Shader* shader, Camera* camera);

		void SetObjectsActive(bool value);

		Transform transform;

	private:
		void UpdateTransform();

		std::vector<GameObject*> m_objects;

		const char* layerName;
		const int layerId;
		int objectCount;
	};
}
#endif