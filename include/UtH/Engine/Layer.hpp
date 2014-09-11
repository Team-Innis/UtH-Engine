#pragma once
#ifndef LAYER_H_UTH
#define LAYER_H_UTH

#include <UtH/Platform/Uncopyable.hpp>
#include <UtH/Engine/GameObject.hpp>

#include <set>

namespace uth
{
	class Layer : private Uncopyable
	{
	public:

		Layer(const int layerId, const bool adoptObjects = true);
		~Layer();

		int GetLayerId() const;

        void SetActive(const bool active);
        bool IsActive() const;

		bool AddGameObject(GameObject* gameObject);
		GameObject* RemoveGameObject(GameObject* gameObject);

		void Update(float dt);
		void Draw(RenderTarget& target);

	private:

		std::set<GameObject*> m_objects;

		const int layerId;
        const bool m_adopt;
        bool m_active;
	};
}
#endif