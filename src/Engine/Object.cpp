#include <UtH/Engine/Object.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <cassert>

namespace uth
{
	Object::Object()
		: m_active(true)
	{

	}

	Object::Object(std::weak_ptr<Object> p)
		: m_parent(p),
		  m_active(true)
	{

	}

	Object::Object(const std::string& tag)
		: Object()
	{
		AddTag(tag);
	}

	Object::Object(const std::string& tag, std::weak_ptr<Object> p)
		: Object(p)
	{
		AddTag(tag);
	}

	Object::Object(const std::vector<std::string>& tags)
		: Object()
	{
		AddTags(tags);
	}

	Object::Object(const std::vector<std::string>& tags, std::weak_ptr<Object> p)
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
			for (auto& i : m_children)
			{
				if (i->m_active)
					i->Update(dt);
			}
		}
	}

	void Object::Draw(RenderTarget& target)
	{
		if (m_active)
		{
			for (auto& i : m_children)
			{
				if (i->m_active)
					i->Draw(target);
			}
		}
	}

	bool Object::HasChild(std::shared_ptr<Object> object)
	{
		return std::find(m_children.begin(), m_children.end(), object) != m_children.end();
	}

	void Object::RemoveChild(std::shared_ptr<Object> object)
	{
		auto o = find(m_children.begin(), m_children.end(), object);
		m_children.erase(o);
	}

	void Object::RemoveChildren()
	{
		m_children.clear();
	}

	void Object::RemoveChildren(const std::string& tag)
	{
		m_children.erase(
			std::remove_if( m_children.begin(), m_children.end(),
			[tag](std::shared_ptr<Object> const& o){return o->HasTag(tag); }
			),
			m_children.end()
		);
	}

	void Object::RemoveChildren(const std::vector<std::shared_ptr<Object>>& objects)
	{
		for (auto o : objects)
		{
			RemoveChild(o);
		}
	}

	std::vector<std::shared_ptr<Object>> Object::ExtractChildren(const std::string& tag)
	{
		const auto it = std::remove_if(m_children.begin(), m_children.end(),
			[tag](std::shared_ptr<Object> const& o){return o->HasTag(tag); });
		std::vector<std::shared_ptr<Object>> retVal(it, m_children.end());
		m_children.erase(it, m_children.end());
		return retVal;
	}

	std::vector<std::shared_ptr<Object>> Object::Children() const
	{
		return m_children;
	}

	std::vector<std::shared_ptr<Object>> Object::Children(const std::string& tag)
	{
		const auto it = std::remove_if(m_children.begin(), m_children.end(),
			[tag](std::shared_ptr<Object> const& o){return o->HasTag(tag); });
		std::vector<std::shared_ptr<Object>> retVal(it, m_children.end());
		return retVal;
	}

	//bool Object::InWorld() const
	//{
	//	return m_inWorld;
	//}

	void Object::AddTags(const std::vector<std::string>& tags)
	{
		for (auto tag : tags)
		{
			AddTag(tag);
		}
	}

	void Object::AddTag(const std::string& tag)
	{
		if (!HasTag(tag))
			m_tagList.push_back(tag);
	}

	bool Object::HasTag(const std::string& tag) const
	{
		return std::find(m_tagList.begin(), m_tagList.end(), tag) == m_tagList.end();
	}

	void Object::RemoveTag(const std::string& tag)
	{
		m_tagList.erase(std::find(m_tagList.begin(), m_tagList.end(), tag));
	}

	const std::vector<std::string>& Object::Tags() const
	{
		return m_tagList;
	}

	std::shared_ptr<Object> Object::Parent()
	{
		assert(HasParent());
		return m_parent.lock();
	}

	void Object::SetParent(std::weak_ptr<Object> p)
	{
		p.lock()->AddChild(std::shared_ptr<Object>(this));
	}

	bool Object::HasParent()
	{
		return !m_parent.expired();
	}

	void Object::setParent(std::weak_ptr<Object> p)
	{
		m_parent = p;
	}
}
