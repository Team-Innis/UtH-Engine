#pragma once
#ifndef OBJECT_H_UTH
#define OBJECT_H_UTH

#include <vector>

namespace uth
{
	class RenderTarget;

	class Object
	{
	public:
		Object(const std::string &name, Object* parent);
		Object(Object* parent);
		~Object();

		virtual void Update(float dt);
		virtual void Draw(RenderTarget& target);

		template <typename T:Object>
		T& AddObject(T* o = new T());
		void RemoveObject(Object&);

		std::vector<Object*> getChilds();

		bool inWorld;

		Object* parent;
	private:
		std::vector<Object*> childs;
		std::string m_name;
	};

	template<typename T:Object>
	T& Object::AddObject(T* o)
	{
		childs.push_back(o);
		if (inWorld)
			o->inWorld = true;
		return *o;
	}
}

#endif