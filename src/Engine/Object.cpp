#include <UtH/Engine/Object.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <cassert>

namespace uth
{
	Object::Object()
		: transform(this),
		m_parent(nullptr),
		m_active(true)
	{

	}
	Object::Object(Object* p)
		: transform(this), 
		m_parent(p),
		m_active(true)
	{

	}
	Object::Object(const std::string& tag)
		: Object()
	{
		AddTag(tag);
	}
	Object::Object(const std::string& tag, Object* p)
		: Object(p)
	{
		AddTag(tag);
	}
	Object::Object(const std::vector<std::string>& tags)
		: Object()
	{
		AddTags(tags);
	}
	Object::Object(const std::vector<std::string>& tags, Object* p)
		: Object(p)
	{
		AddTags(tags);
	}
	Object::~Object()
	{
		RemoveChildren();
	}

	void Object::Update(float dt)
	{
		if (m_active)
		{
			for (auto i = 0; i < m_children.size(); i++)
			{
				auto& c = m_children[i];
				if (c->IsActive())
					c->Update(dt);
			}
		}
	}
	void Object::Draw(RenderTarget& target, RenderAttributes attributes)
	{
		if (m_active)
		{
			for (auto& i : m_children)
			{
				if (i->m_active)
					i->Draw(target, attributes);
			}
		}
	}

	bool Object::HasChild(const std::shared_ptr<Object>& object) const
	{
		return std::find(m_children.begin(), m_children.end(), object) != m_children.end();
	}

	void Object::RemoveChild(const std::shared_ptr<Object>& object)
	{
		auto o = std::find(m_children.begin(), m_children.end(), object);
		(*o)->setParent(nullptr);
		m_children.erase(o);
	}
	void Object::RemoveChildren()
	{
		for (auto& child : m_children)
			child->setParent(nullptr);
		m_children.clear();
	}
	void Object::RemoveChildren(const std::string& tag)
	{
		RemoveChildren(Children(tag));

		//m_children.erase(
		//	std::remove_if( m_children.begin(), m_children.end(),
		//	[tag](std::shared_ptr<Object> const& o)
		//{
		//	return o->HasTag(tag); 
		//}
		//	),
		//	m_children.end()
		//);
	}
	void Object::RemoveChildren(const std::vector<std::shared_ptr<Object>>& objects)
	{
		for (auto& o : objects)
		{
			RemoveChild(o);
		}
	}

	std::vector<std::shared_ptr<Object>> Object::ExtractChildren(const std::string& tag)
	{
		std::vector<std::shared_ptr<Object>> retVal;
		for (auto it = m_children.begin(); it != m_children.end(); it++)
		{
			if ((*it)->HasTag(tag))
			{
				retVal.push_back(*it);
				m_children.erase(it);
			}
		}
		return retVal;

		//const auto it = std::remove_if(m_children.begin(), m_children.end(),
		//	[tag](std::shared_ptr<Object> const& o)
		//{
		//	return o->HasTag(tag);
		//});
		//std::vector<std::shared_ptr<Object>> retVal(it, m_children.end());
		//m_children.erase(it, m_children.end());
		//return retVal;
	}

	std::vector<std::shared_ptr<Object>> Object::Children() const
	{
		return m_children;
	}
	std::vector<std::shared_ptr<Object>> Object::Children(const std::string& tag) const
	{
		std::vector<std::shared_ptr<Object>> retVal;
		for (auto it = m_children.begin(); it != m_children.end(); it++)
		{
			if ((*it)->HasTag(tag))
			{
				retVal.push_back(*it);
			}
		}
		return retVal;

		//if (m_children.size() == 0)
		//	return m_children;
		//const auto it = std::remove_if(m_children.begin(), m_children.end(),
		//	[tag](std::shared_ptr<Object> const& o)
		//{
		//	return o->HasTag(tag); 
		//});
		//std::vector<std::shared_ptr<Object>> retVal(it, m_children.end());
		//return retVal;
	}

	std::vector<std::shared_ptr<Object>> Object::FindAll(const std::string& tag, const size_t reserveSize)
	{
		std::vector<std::shared_ptr<Object>> retVal;
		retVal.reserve(reserveSize);
		findAll(tag, retVal);
		return retVal;
	}
	std::vector<std::shared_ptr<Object>> Object::FindAll(const size_t reserveSize)
	{
		std::vector<std::shared_ptr<Object>> retVal;
		retVal.reserve(reserveSize);
		findAll(retVal);
		return retVal;
	}

	//bool Object::InWorld() const
	//{
	//	return m_inWorld;
	//}

	void Object::AddTags(const std::vector<std::string>& tags)
	{
		for (auto& tag : tags)
		{
			AddTag(tag);
		}
	}
	void Object::AddTag(const std::string& tag)
	{
		if (!HasTag(tag))
			m_tagList.emplace(tag);
	}
	bool Object::HasTag(const std::string& tag) const
	{
		return m_tagList.find(tag) != m_tagList.end();
	}
	void Object::RemoveTag(const std::string& tag)
	{
		m_tagList.erase(std::find(m_tagList.begin(), m_tagList.end(), tag));
	}
	const std::unordered_set<std::string>& Object::Tags() const
	{
		return m_tagList;
	}

	Object* Object::Parent() const
	{
		//assert(HasParent());
		return m_parent;
	}
	bool Object::HasParent() const
	{
		return m_parent != nullptr;
	}

	void Object::SetActive(bool value)
	{
		m_active = value;
	}
	bool Object::IsActive() const
	{
		return m_active;
	}

// Private

	void Object::findAll(const std::string& tag, std::vector<std::shared_ptr<Object>>& vec) const
	{
		if (m_children.size() == 0)
			return;
		auto v = Children(tag);
		if (v.size() != 0)
			vec.insert(vec.end(), v.begin(), v.end());
		for (auto& o : m_children)
		{
			o->findAll(tag, vec);
		}
	}
	void Object::findAll(std::vector<std::shared_ptr<Object>>& vec) const
	{
		if (m_children.size() == 0)
			return;
		auto v = Children();
		if (v.size() != 0)
			vec.insert(vec.end(), v.begin(), v.end());
		for (auto& o : m_children)
		{
			o->findAll(vec);
		}
	}

	void Object::setParent(Object* p)
	{
		m_parent = p;
	}
}
