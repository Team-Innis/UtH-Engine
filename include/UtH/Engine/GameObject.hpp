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
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void AddComponent(Component* component);
		Component* GetComponent(const std::string name);
		void RemoveComponent(Component* component);
		void RemoveComponent(std::string name);

		void Draw(Shader* shader);
		void Update(float dt);

		// Transform is a special component that every gameobject has
		Transform transform;

	private:
		std::vector<Component*> updateComponents;
		std::vector<Component*> drawComponents;		
	};
}
#endif