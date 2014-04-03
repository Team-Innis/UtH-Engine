#pragma once
#ifndef LAYER_H_UTH
#define LAYER_H_UTH

#include <UtH/Platform/Uncopyable.hpp>
#include <UtH/Engine/GameObject.hpp>

#include <vector>

namespace uth
{
	class Layer : private Uncopyable 
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

		void Update(float dt);
		void Draw(RenderTarget& target);

		void SetObjectsActive(bool value);

		Transform transform;

	private:
		void UpdateTransform();

		std::vector<GameObject*> m_objects;

		const char* layerName;
		const int layerId;
		unsigned int objectCount;
	};
}
#endif