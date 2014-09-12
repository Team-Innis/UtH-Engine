#pragma once
#ifndef LAYER_H_UTH
#define LAYER_H_UTH

#include <UtH/Platform/Uncopyable.hpp>
#include <set>

namespace uth
{
    class GameObject;
    class RenderTarget;

	class Layer : private Uncopyable
	{

        friend class Scene;

	public:

		int GetLayerId() const;

        void SetActive(const bool active);
        bool IsActive() const;

		bool AddGameObject(GameObject* gameObject);
		GameObject* RemoveGameObject(GameObject* gameObject, const bool deleteObject = true);

		void Update(float dt);
		void Draw(RenderTarget& target);

    private:

        Layer(const int layerId, const bool adoptObjects = true);
        ~Layer();

		std::set<GameObject*> m_objects;

		const int layerId;
        const bool m_adopt;
        bool m_active;
	};
}
#endif