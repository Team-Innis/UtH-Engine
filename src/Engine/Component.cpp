#include <UtH/Engine/Component.hpp>

using namespace uth;

Component::Component()
	: parent(nullptr),
	  m_name(""),
	  m_active(false)
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