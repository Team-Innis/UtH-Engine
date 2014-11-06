#include <UtH/Engine/Component.hpp>

using namespace uth;

Component::Component()
	: Component("Component")
{
}

Component::Component(const std::string& name)
	: parent(nullptr),
	  m_name(name),
	  m_active(true)
{
}

Component::~Component()
{
}

void Component::SetActive(bool active)
{
	m_active = active;
}

const bool Component::IsActive() const
{
	return m_active;
}

void Component::SetName(const std::string& name)
{
	m_name = name;
}

const std::string& Component::GetName() const
{
	return m_name;
}

namespace rj = rapidjson;

rj::Value uth::Component::save(rj::MemoryPoolAllocator<>& alloc) const
{
    rj::Value val;
    val.SetObject();

    val.AddMember(rj::StringRef("name"), rj::Value(m_name.c_str(), alloc), alloc);
    val.AddMember(rj::StringRef("active"), m_active, alloc);

    return val;
}

bool uth::Component::load(const rapidjson::Value& doc)
{
    if (!doc.HasMember("name") || !doc.HasMember("active"))
        return false;

    SetName(doc["name"].GetString());
    SetActive(doc["active"].GetString());

    return true;
}

const char* uth::Component::getIdentifier() const
{
    return "Component";
}
