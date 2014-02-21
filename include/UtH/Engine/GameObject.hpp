#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

#include <UtH/Engine/Component.hpp>
#include <UtH/Math/Math.hpp>

namespace uth
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		void RemoveComponent(std::string name);

		void Move(umath::vector2 offset);
		void Move(int offsetX, int offsetY);

		void SetPosition(umath::vector2 position);
		void SetPosition(int posX, int posY);
		const umath::vector2 GetPosition() const;

		void Resize(umath::vector2 size);
		void Resize(int width, int height);
		const umath::vector2 GetSize() const;
		
		void SetRotation(float angle);
		float GetRotation();
		void Rotate(float angle);

		void Draw();
		void Update(float dt);

	private:
		void updateTransform();

		std::vector<Component*> updateComponents;
		std::vector<Component*> drawComponents;

		umath::rectangle m_dimensions;
		float m_angle;

		umath::matrix4 m_modelTransform;
	};
}
#endif