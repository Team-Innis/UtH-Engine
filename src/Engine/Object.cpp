#include <UtH/Engine/Object.hpp>

namespace uth
{
	Object::Object(Object* p)
		: parent(p),
		m_inWorld(false)
	{

	}

	Object::Object(Object* p, const std::string& tag)
		: parent(p),
		m_inWorld(false)
	{
		AddTag(tag);
	}

	Object::Object(Object* p, const std::vector<std::string>& tags)
		: parent(p),
		m_inWorld(false)
	{
		AddTags(tags);
	}

	Object::Object(Object& p)
		: Object(&p)
	{}

	Object::Object(Object& p, const std::string& tag)
		: Object(&p, tag)
	{}

	Object::Object(Object& p, const std::vector<std::string>& tags)
		: Object(&p,tags)
	{}

	Object::~Object()
	{

	}

	void Object::Update(float dt)
	{
		if (active)
		{
			for (auto& i : m_children)
			{
				if (i->active)
					i->Update(dt);
			}
		}
	}

	void Object::Draw(RenderTarget& target)
	{
		if (active)
		{
			for (auto& i : m_children)
			{
				if (i->active)
					i->Draw(target);
			}
		}
	}

	void Object::RemoveChild(Object* object)
	{
		auto o = find(m_children.begin(), m_children.end(), object);
		m_children.erase(o);
	}

	void Object::RemoveChild(Object& object)
	{
		RemoveChild(&object);
	}

	struct childEraser
	{
		childEraser(const std::string& tag)
			: m_tag(tag)
		{

		}
		const std::string& m_tag;
		bool operator()(const std::unique_ptr<Object> o)
		{
			return o->HasTag(m_tag);
		}
	};

	void Object::RemoveChildren(const std::string& tag)
	{
		m_children.erase(
			std::remove_if(m_children.begin(), m_children.end(), childEraser(tag)), 
			m_children.end()
		);

	}

	void Object::RemoveChildren(const std::vector<Object*>& objects)
	{
		for (auto o : objects)
		{
			RemoveChild(o);
		}
	}

	std::vector<Object*> Object::ExtractChildren(const std::string& tag)
	{
		const auto it = std::remove_if(m_children.begin(), m_children.end(), childEraser(tag));
		std::vector<Object*> retVal(it, m_children.end());
		m_children.erase(it, m_children.end());
		return retVal;
	}

	std::vector<Object*> Object::Children() const
	{
		return std::vector<Object*>(m_children.begin(),m_children.end());
	}

	std::vector<Object*> Object::Children(const std::string& tag) const
	{
		const auto it = std::remove_if(m_children.begin(), m_children.end(), childEraser(tag));
		std::vector<Object*> retVal(it, m_children.end());
		return retVal;
	}

	bool Object::InWorld() const
	{
		return m_inWorld;
	}

	void Object::AddTags(const std::vector<std::string>& tags)
	{
		for (auto tag : tags)
		{
			AddTag(tag);
		}
	}

	void Object::AddTag(const std::string& tag)
	{
		if (std::find(m_tagList.begin(), m_tagList.end(), tag) == m_tagList.end())
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

	std::vector<std::string> Object::Tags() const
	{
		return m_tagList;
	}
}
