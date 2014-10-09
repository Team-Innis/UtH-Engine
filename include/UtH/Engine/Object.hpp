#pragma once
#ifndef OBJECT_H_UTH
#define OBJECT_H_UTH

#include <algorithm>
#include <vector>
#include <unordered_set>
#include <string>
#include <memory>
#include <UtH/Engine/Transform.hpp>
#include <UtH/Renderer/RenderAttributes.hpp>

namespace uth
{
	class RenderTarget;

	class Object
	{
		Object(const Object&) = delete;
	public:
		Object();
		Object(Object* parent);
		Object(const std::string& tag);
		Object(const std::string& tag, Object* parent);
		Object(const std::vector<std::string>& tags);
		Object(const std::vector<std::string>& tags, Object* parent);
		virtual ~Object();

		virtual void Update(float dt);
		virtual void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes());

		template <typename T>
		std::shared_ptr<T> AddChild(std::shared_ptr<T> object);
		template <typename T>
		std::shared_ptr<T> AddChild(T* object = new T());

		bool HasChild(const std::shared_ptr<Object>& object) const;

		void RemoveChild(const std::shared_ptr<Object>& object);
		void RemoveChildren();
		void RemoveChildren(const std::string& tag);
		void RemoveChildren(const std::vector<std::shared_ptr<Object>>& objects);

		template <typename T>
		std::shared_ptr<T> ExtractChild(const std::shared_ptr<T>& object);

		std::vector<std::shared_ptr<Object>> ExtractChildren(const std::string& tag);

		std::vector<std::shared_ptr<Object>> Children() const;
		std::vector<std::shared_ptr<Object>> Children(const std::string& tag) const;

		std::vector<std::shared_ptr<Object>> FindAll(const std::string& tag, const size_t reserveSize = 100);
		std::vector<std::shared_ptr<Object>> FindAll(const size_t reserveSize = 100);

		//bool InWorld() const;

		void AddTags(const std::vector<std::string>& tags);
		void AddTag(const std::string& tag);
		bool HasTag(const std::string& tag) const;
		void RemoveTag(const std::string& tag);
		const std::unordered_set<std::string>& Tags() const;

		template <typename T>
		T* Parent() const;
		Object* Parent() const;

		template <typename T>
		bool HasParent() const;
		bool HasParent() const;

		void SetActive(bool value);
		bool IsActive() const;

		Transform transform;

	protected:
		Object* m_parent;
		bool m_active;

	private:
		void findAll(const std::string& tag, std::vector<std::shared_ptr<Object>>& vec) const;
		void findAll(std::vector<std::shared_ptr<Object>>& vec) const;

		void setParent(Object* p);
		//bool m_inWorld;
		std::vector<std::shared_ptr<Object>> m_children;
		std::unordered_set<std::string> m_tagList;
	};

	template <typename T>
	inline std::shared_ptr<T> Object::AddChild(std::shared_ptr<T> object)
	{
		if (object != nullptr)
		{
			m_children.push_back(object);

			object->setParent(this);
			//if (InWorld)
			//	object->m_inWorld = true;
		}
		return object;
	}

	template <typename T>
	inline std::shared_ptr<T> Object::AddChild(T* object /*= new T()*/)
	{
		return AddChild(std::shared_ptr<T>(object));
	}

	template <typename T>
	inline std::shared_ptr<T> Object::ExtractChild(const std::shared_ptr<T>& object)
	{
		auto it = std::find(m_children.begin(), m_children.end(), object);
		if (it == m_children.end())
			return nullptr;
		const std::shared_ptr<Object> retVal = &*it;
		it->release();
		m_children.erase(it);
		return retVal;
	}

	template <typename T>
	inline T* Object::Parent() const
	{
		//assert(HasParent<T>());
		return dynamic_cast<T*>(Parent());
	}

	template <typename T>
	inline bool Object::HasParent() const
	{
		return dynamic_cast<T*>(Parent()) != nullptr;
	}

    typedef Object Layer;
}

#endif
