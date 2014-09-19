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
		Object(std::weak_ptr<Object> parent);
		Object(std::weak_ptr<Object> parent, const std::string& tag);
		Object(std::weak_ptr<Object> parent, const std::vector<std::string>& tags);
		virtual ~Object();

		virtual void Update(float dt);
		virtual void Draw(RenderTarget& target);

		template <typename T>
		std::shared_ptr<T> AddChild(std::shared_ptr<T> object = new T());

		void RemoveChild(std::shared_ptr<Object> object);
		void RemoveChildren();
		void RemoveChildren(const std::string& tag);
		void RemoveChildren(const std::vector<std::shared_ptr<Object>>& objects);

		template <typename T>
		std::shared_ptr<T> ExtractChild(std::shared_ptr<T> object);

		std::vector<std::shared_ptr<Object>> ExtractChildren(const std::string& tag);

		std::vector<std::shared_ptr<Object>> Children() const;
		std::vector<std::shared_ptr<Object>> Children(const std::string& tag);

		//bool InWorld() const;

		void AddTags(const std::vector<std::string>& tags);
		void AddTag(const std::string& tag);
		bool HasTag(const std::string& tag) const;
		void RemoveTag(const std::string& tag);
		std::vector<std::string> Tags() const;

		template <typename T>
		std::shared_ptr<T> Parent();
		std::shared_ptr<Object> Parent();
		void SetParent(std::weak_ptr<Object> p);

		bool active;

	protected:
		std::weak_ptr<Object> m_parent;

	private:
		void setParent(std::weak_ptr<Object> p);
		bool m_inWorld;
		std::vector<std::shared_ptr<Object>> m_children;
		std::vector<std::string> m_tagList;
	};

	template <typename T>
	std::shared_ptr<T> Object::AddChild(std::shared_ptr<T> object /*= new T()*/)
	{
		m_children.emplace_back(object);
		object->setParent(std::shared_ptr<Object>(this));
		//if (InWorld)
		//	object->m_inWorld = true;
		return object;
	}

	template <typename T>
	std::shared_ptr<T> Object::ExtractChild(std::shared_ptr<T> object)
	{
		auto it = std::find(m_children.begin(), m_children.end(), object);
		if (it-> == m_children.end())
			return nullptr;
		const std::shared_ptr<Object> retVal = &*it;
		it->release();
		m_children.erase(it);
		return retVal;
	}

	template <typename T>
	std::shared_ptr<T> Parent()
	{
		assert(dynamic_pointer_cast(Parent()));
		return dynamic_pointer_cast(Parent());
	}
}

#endif
