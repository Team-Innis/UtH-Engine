#pragma once
#ifndef LAYER_H_UTH
#define LAYER_H_UTH

#include <UtH/Platform/Uncopyable.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <set>

namespace uth
{
    class GameObject;
    class RenderTarget;

	class Layer : private Uncopyable
	{

        friend class Scene;

        GameObject m_gameObject;

	public:

        void Clear();

		int GetLayerId() const;

        void SetActive(const bool active);
        bool IsActive() const;

		GameObject* AddGameObject(GameObject* gameObject);
		GameObject* RemoveGameObject(GameObject* gameObject, const bool deleteObject = true);
        GameObject* GetGameObject(const std::string& name);
        bool HasGameObject(GameObject* gameObject);

		void Update(float dt);
		void Draw(RenderTarget& target);


        Transform& transform;

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