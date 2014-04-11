#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

#include <UtH/Engine/Component.hpp>
#include <UtH/Math/Math.hpp>
#include <UtH/Engine/Transform.hpp>

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
		Component* GetComponent(const std::string& name);
		// Will actually delete the component
		void RemoveComponent(Component* component);
		void RemoveComponent(const std::string& name);
		void RemoveComponents();

		virtual void Draw(RenderTarget& target);
		virtual void Update(float dt);

		// Transform is a special component that every gameobject has
		Transform transform;

		GameObject* parent;

	private:
		std::vector<Component*> components;

		bool m_active;
	};
}
#endif