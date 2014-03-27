#pragma once
#ifndef COMPONENT_H_UTH
#define COMPONENT_H_UTH

#include <string>
#include <UtH/Core/Shader.hpp>

namespace uth
{
	class GameObject;
	class Camera;

	class Component
	{
	public:

		Component(const std::string& name); // Should be unique(per gameobject)
		virtual ~Component();

		virtual void SetActive(bool active);
		const bool IsActive() const;

		void SetName(const std::string& name);
		const std::string GetName() const;

		// Default to doing nothing
		virtual void Draw(Shader* shader, Camera* camera){};
		virtual void Update(float dt){};

		GameObject* parent;

	protected:
		Component();

		std::string m_name;

		bool m_active;		
	};
}
#endif