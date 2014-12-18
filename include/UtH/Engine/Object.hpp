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
#include <UtH/Engine/Saveable.hpp>


namespace uth
{
	class RenderTarget;

	class Object : public Saveable
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

		template<typename T>
		std::shared_ptr<T> AddChild(std::shared_ptr<T> object, const bool keepGlobalPos = false);
		template<typename T>
		std::shared_ptr<T> AddChild(T* object = new T(), const bool keepGlobalPos = false);
		void AddChildren(const std::vector<std::shared_ptr<Object>>& objects, const bool keepGlobalPos = false);
		void AddChildren(const std::vector<Object*>& objects, const bool keepGlobalPos = false);

		bool HasChild(const std::shared_ptr<Object>& object) const;
		bool HasChild(const Object* object) const;

		void RemoveChild(const std::shared_ptr<Object>& object);
		void RemoveChild(Object* object);
		void RemoveChildren();
		void RemoveChildren(const std::string& tag);
		void RemoveChildren(const std::vector<std::shared_ptr<Object>>& objects);
		void RemoveChildren(const std::vector<Object*>& objects);
		void Remove();			// Marks for deletion
		bool IsRemoved() const; // Check deletion mark

		template <typename T>
		std::shared_ptr<Object> ExtractChild(const std::shared_ptr<T>& object, const bool keepGlobalPos = false);
		template <typename T>
		std::shared_ptr<Object> ExtractChild(const T* object, const bool keepGlobalPos = false);

		std::vector<std::shared_ptr<Object>> ExtractChildren(const std::string& tag, const bool keepGlobalPos = false);

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

        rapidjson::Value save(rapidjson::MemoryPoolAllocator<>& alloc) const override;
        bool load(const rapidjson::Value& doc) override;

	private:

        friend class SceneManager;

		void findAll(const std::string& tag, std::vector<std::shared_ptr<Object>>& vec) const;
		void findAll(std::vector<std::shared_ptr<Object>>& vec) const;

		void setParent(Object* p);

		std::vector<std::shared_ptr<Object>> m_children;
		std::unordered_set<std::string> m_tagList;
		bool m_isRemoved = false; // Whether or not this Object is about the be deleted
	};

	template <typename T>
	inline std::shared_ptr<T> Object::AddChild(std::shared_ptr<T> object, const bool keepGlobalPos)
	{
		static_assert(std::is_void<T>::value || std::is_base_of<Object, T>::value, "Error: Template type must be derived from uth::Object");

		if (object != nullptr)
		{
			if (keepGlobalPos)
				object->transform.SetTransform(object->transform.GetTransform()*transform.GetTransform().inverse());

			m_children.push_back(object);

			object->setParent(this);
		}

		return object;
	}
	template <typename T>
	inline std::shared_ptr<T> Object::AddChild(T* object, const bool keepGlobalPos)
	{
		return AddChild(std::shared_ptr<T>(object),keepGlobalPos);
	}

	template <typename T>
	inline std::shared_ptr<Object> Object::ExtractChild(const std::shared_ptr<T>& object, const bool keepGlobalPos)
	{
		static_assert(std::is_void<T>::value || std::is_base_of<Object, T>::value, "Error: Template type must be derived from uth::Object");

		auto it = std::find(m_children.begin(), m_children.end(), object);
		if (it == m_children.end())
			return nullptr;
		const std::shared_ptr<Object> retVal = *it;

		if (keepGlobalPos)
			retVal->transform.SetTransform(retVal->transform.GetTransform());
		retVal->setParent(nullptr);

		m_children.erase(it);
		return retVal;
	}
	template <typename T>
	inline std::shared_ptr<Object> Object::ExtractChild(const T* object, const bool keepGlobalPos)
	{
		static_assert(std::is_void<T>::value || std::is_base_of<Object, T>::value, "Error: Template type must be derived from uth::Object");

		for (auto it = m_children.begin(); it != m_children.end(); it++)
		{
			if ((*it).get() == object)
			{
				if (dynamic_cast<T*>((*it).get()) == nullptr)
					return nullptr;
				const std::shared_ptr<Object> retVal = *it;

				if (keepGlobalPos)
					retVal->transform.SetTransform(retVal->transform.GetTransform());
				retVal->setParent(nullptr);

				m_children.erase(it);
				return retVal;
			}
		}
		return nullptr;
	}

	template <typename T>
	inline T* Object::Parent() const
	{
		static_assert(std::is_void<T>::value || std::is_base_of<Object, T>::value, "Error: Template type must be derived from uth::Object");

		//assert(HasParent<T>());
		return dynamic_cast<T*>(Parent());
	}

	template <typename T>
	inline bool Object::HasParent() const
	{
		static_assert(std::is_void<T>::value || std::is_base_of<Object, T>::value, "Error: Template type must be derived from uth::Object");

		return dynamic_cast<T*>(Parent()) != nullptr;
	}

	typedef Object Layer;
}

#endif
