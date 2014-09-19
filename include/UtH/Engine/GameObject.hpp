#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <UtH/Engine/Component.hpp>
#include <UtH/Engine/Transform.hpp>
#include <UtH/Engine/Object.hpp>
#include <pmath/PMath.hpp>

#include <vector>
#include <string>
#include <memory>


namespace uth
{
	class Camera;

	class GameObject : public Object
	{
	public:
		GameObject();
		GameObject(const std::string &tag);
        //GameObject(const GameObject& other);
        void operator =(const GameObject&) = delete;
		virtual ~GameObject();

		void AddComponent(Component* component);
        template<typename T>
		T* GetComponent(const std::string& name);
		// Will actually delete the component
		void RemoveComponent(Component* component);
		void RemoveComponent(const std::string& name);
		void RemoveComponents();

		void Draw(RenderTarget& target) final;
		void Update(float dt) final;

		// Transform is a special component that every gameobject has

	protected:
        virtual void update(float){};
        virtual void draw(RenderTarget& target);

		std::vector<std::unique_ptr<Component>> components;
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