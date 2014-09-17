#pragma once
#ifndef OBJECT_H_UTH
#define OBJECT_H_UTH

#include <algorithm>
#include <vector>
#include <string>
#include <memory>

namespace uth
{
	class RenderTarget;

	class Object
	{
		Object(const Object&) = delete;
	public:
		Object(Object* parent, const std::vector<std::string>& tags);
		Object(Object* parent, const std::string& tag);
		Object(Object* parent);
		Object(Object& parent, const std::vector<std::string>& tags);
		Object(Object& parent, const std::string& tag);
		Object(Object& parent);
		virtual ~Object();

		virtual void Update(float dt);
		virtual void Draw(RenderTarget& target);

		template <typename T>
		T& AddChild(T* object = new T());

		void RemoveChild(Object* object);
		void RemoveChild(Object& object);
		void RemoveChildren(const std::string& tag);

		template <typename T>
		T* ExtractChild(T* object);
		template <typename T>
		T* ExtractChild(T& object);

		std::vector<Object*> ExtractChildren(const std::string& tag);

		std::vector<Object*> Children() const;
		std::vector<Object*> Children(const std::string& tag) const;

		bool InWorld() const;

		bool HasTag(const std::string& tag) const;

		Object* parent;
		bool active;
	private:
		bool m_inWorld;
		std::vector<std::unique_ptr<Object>> m_children;
		std::vector<std::string> m_tagList;
	};

	template<typename T>
	T& Object::AddChild(T* o)
	{
		m_children.emplace_back(o);
		if (InWorld)
			o->inWorld = true;
		return *o;
	}

	template <typename T>
	T* Object::ExtractChild(T* object)
	{
		auto it = std::find(m_children.begin(), m_children.end(), object);
		if (it-> == m_children.end())
			return nullptr;
		const Object* retVal = &*it;
		it->release();
		m_children.erase(it);
		return retVal;
	}
	template <typename T>
	T* Object::ExtractChild(T& object)
	{
		return ExtractChild(&object);
	}
}

#endif