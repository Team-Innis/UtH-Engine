#pragma once
#ifndef COMPONENT_H_UTH
#define COMPONENT_H_UTH

#include <string>

namespace uth
{
	class Component
	{
	public:

		Component(std::string name); // Should be unique(per gameobject)
		virtual ~Component();

		void SetActive(bool active);
		bool GetActive();

		void SetDrawable(bool drawable);
		bool GetDrawable();

		void SetDynamic(bool dynamic);
		bool GetDynamic();

		void SetName(std::string name);
		std::string GetName();

		virtual void Draw();
		virtual void Update(float dt);
	protected:
		Component();

	private:
		std::string m_name;

		bool m_active;
		bool m_draw;
		bool m_dynamic; // false = static
		
	};
}
#endif