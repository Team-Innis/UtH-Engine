#include <UtH/Engine/Object.hpp>

namespace uth
{
	Object::Object(Object* p, const std::vector<std::string>& tags)
		: parent(p),
		m_inWorld(false)
	{

	}

	Object::Object(Object* p, const std::string& tag)
		: parent(p),
		m_inWorld(false)
	{

	}

	Object::Object(Object* p)
		: parent(p),
		m_inWorld(false)
	{

	}

	Object::Object(Object& p, const std::vector<std::string>& tags)
		: Object(&p,tags)
	{

	}

	Object::Object(Object& p, const std::string& tag)
		: Object(&p, tag)
	{

	}

	Object::Object(Object& p)
		: Object(&p)
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

	std::vector<Object*> Object::ExtractChildren(const std::string& tag)
	{

	}

	std::vector<Object*> Object::Children() const
	{

	}

	std::vector<Object*> Object::Children(const std::string& tag) const
	{

	}

	bool Object::InWorld() const
	{
		return m_inWorld;
	}

	bool Object::HasTag(const std::string& tag) const
	{

	}
}
