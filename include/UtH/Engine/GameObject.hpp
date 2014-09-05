#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <UtH/Engine/Component.hpp>
#include <UtH/Engine/Transform.hpp>
#include <pmath/PMath.hpp>

#include <vector>
#include <string>
#include <memory>


namespace uth
{
	class Camera;

	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		void SetActive(bool value);
		const bool IsActive() const;

		void AddComponent(Component* component);
        template<typename T>
        T* GetComponent(const std::string& name);
		// Will actually delete the component
		void RemoveComponent(Component* component);
		void RemoveComponent(const std::string& name);
		void RemoveComponents();

		void Draw(RenderTarget& target);
		void Update(float dt);

		// Transform is a special component that every gameobject has
		Transform transform;

		GameObject* parent;

	protected:
        virtual void update(float){};
        virtual void draw(RenderTarget& target);

		std::vector<std::unique_ptr<Component>> components;

		bool m_active;
	};


    template<typename T>
    T* GameObject::GetComponent(const std::string& name)
    {
        for (size_t i = 0; i < components.size(); ++i)
        {
            if (components.at(i)->GetName() == name)
            {
                return dynamic_cast<T*>(components[i].get());
            }
        }

        return nullptr;
    }
}
#endif