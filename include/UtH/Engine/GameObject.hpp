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
		GameObject(const std::string &name);
        GameObject(const GameObject& other);
        void operator =(const GameObject&) = delete;
		virtual ~GameObject();

		void SetActive(bool value);
		const bool IsActive() const;

		void AddComponent(Component* component);
        template<typename T>
        T* GetComponent(const std::string& name);
		const std::string GetName() const;
		// Will actually delete the component
		void RemoveComponent(Component* component);
		void RemoveComponent(const std::string& name);
		void RemoveComponents();

		void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes());
		void Update(float dt);

		// Transform is a special component that every gameobject has
		Transform& transform;

		GameObject* parent;

	protected:
        virtual void update(float){}
        virtual void draw(RenderTarget&){}

		std::vector<std::unique_ptr<Component>> m_components;
		std::string m_name;

		bool m_active;
	};


    template<typename T>
    T* GameObject::GetComponent(const std::string& name)
    {
        for (size_t i = 0; i < components.size(); ++i)
        {
            if (components.at(i)->GetName() == name)
            {
                return static_cast<T*>(components[i].get());
            }
        }

        return nullptr;
    }
}
#endif