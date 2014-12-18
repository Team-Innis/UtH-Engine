#include <UtH/Engine/Object.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <cassert>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Engine/SceneManager.hpp>

namespace uth
{
	Object::Object()
		: transform(this),
		m_parent(nullptr),
		m_active(true),
		m_isRemoved(false)
	{

	}
	Object::Object(Object* p)
		: transform(this),
		m_parent(p),
		m_active(true),
		m_isRemoved(false)
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
		if (!m_active)
			return;

		const std::vector<std::shared_ptr<Object>> objBackup(m_children);

		for (auto o : objBackup)
		{
			if (o->IsActive())
				o->Update(dt);
			if (o->IsRemoved())
				RemoveChild(o);
		}
	}
	void Object::Draw(RenderTarget& target, RenderAttributes attributes)
	{
		if (!m_active)
			return;

		for (auto& i : m_children)
		{
			if (i->m_active)
				i->Draw(target, attributes);
		}
	}

	void Object::AddChildren(const std::vector<std::shared_ptr<Object>>& objects, const bool keepGlobalPos)
	{
		for (auto& o : objects)
			AddChild(o, keepGlobalPos);
	}
	void Object::AddChildren(const std::vector<Object*>& objects, const bool keepGlobalPos)
	{
		for (auto& o : objects)
			AddChild(o, keepGlobalPos);
	}

	bool Object::HasChild(const std::shared_ptr<Object>& object) const
	{
		return std::find(m_children.begin(), m_children.end(), object) != m_children.end();
	}
	bool Object::HasChild(const Object* object) const
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (object == it->get())
			{
				return true;
			}
		}
		return false;
	}

	void Object::RemoveChild(const std::shared_ptr<Object>& object)
	{
		auto it = std::find(m_children.begin(), m_children.end(), object);
		(*it)->setParent(nullptr);
		m_children.erase(it);
	}
	void Object::RemoveChild(Object* object)
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (object == it->get())
			{
				(*it)->setParent(nullptr);
				m_children.erase(it);
				return;
			}
		}
	}

	void Object::RemoveChildren()
	{
		assert(
			this != nullptr ?
			true :
			[]() -> bool { WriteError("This = nullptr, object deleted multiple times"); return false; }()
			);

		for (auto& child : m_children)
			child->setParent(nullptr);
		m_children.clear();
	}
	void Object::RemoveChildren(const std::string& tag)
	{
		RemoveChildren(Children(tag));
	}
	void Object::RemoveChildren(const std::vector<std::shared_ptr<Object>>& objects)
	{
		for (auto& o : objects)
		{
			RemoveChild(o);
		}
	}
	void Object::RemoveChildren(const std::vector<Object*>& objects)
	{
		for (auto& o : objects)
		{
			RemoveChild(o);
		}
	}
	void Object::Remove()
	{
		m_isRemoved = true;
	}
	bool Object::IsRemoved() const
	{
		return m_isRemoved;
	}

	std::vector<std::shared_ptr<Object>> Object::ExtractChildren(const std::string& tag, const bool keepGlobalPos)
	{
		std::vector<std::shared_ptr<Object>> retVal;
		for (auto it = m_children.begin(); it != m_children.end(); it++)
		{
			const auto& c = (*it);
			if (c->HasTag(tag))
			{
				if (keepGlobalPos)
					c->transform.SetTransform(c->transform.GetTransform());
				retVal.push_back(*it);
				m_children.erase(it);
			}
		}
		return retVal;
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

    namespace rj = rapidjson;

    rj::Value Object::save(rapidjson::MemoryPoolAllocator<>& alloc) const
    {
        rj::Value val;
        val.SetObject();

        // Active flag
        val.AddMember(rj::StringRef("identifier"), rj::StringRef(typeid(*this).raw_name()), alloc);
        val.AddMember(rj::StringRef("active"), m_active, alloc);
        
        val.AddMember(rj::StringRef("transform"), transform.save(alloc), alloc);

        // Tags
        if (!m_tagList.empty())
        {
            rj::Value tagArray;
            tagArray.SetArray();

            for (auto& i : m_tagList)
                tagArray.PushBack(rj::Value(i.c_str(), alloc), alloc);

            val.AddMember(rj::StringRef("tags"), tagArray, alloc);
        }
        
        // Children
        if (!m_children.empty())
        {
            val.AddMember(rj::StringRef("children"), rj::kArrayType, alloc);
            rj::Value& childArray = val["children"];

            for (auto& i : m_children)
                childArray.PushBack(i->save(alloc), alloc);
        }

        return val;
    }

    bool Object::load(const rj::Value& doc)
    {
        m_children.clear();
        m_tagList.clear();

        m_active = doc["active"].GetBool();

        // We'll just assume the transform is valid.
        transform.load(doc["transform"]);

        // Tags
        if (doc.HasMember("tags") && doc["tags"].IsArray())
        {
            const rj::Value& tagArray = doc["tags"];

            for (auto itr = tagArray.Begin(); itr != tagArray.End(); ++itr)
                m_tagList.emplace(itr->GetString());
        }

        // Children
        if (doc.HasMember("children") && doc["children"].IsArray())
        {
            const rj::Value& childArray = doc["children"];

            for (auto itr = childArray.Begin(); itr != childArray.End(); ++itr)
            {
                std::unique_ptr<Object> ptr(static_cast<Object*>(uthSceneM.GetSaveable(*itr)));
                
                if (!ptr)
                    return false;

                if (ptr->load(*itr))
                    AddChild(ptr.release());
                else
                    return false;
            }
        }

        return true;
    }
}
