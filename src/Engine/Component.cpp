#include <UtH/Engine/Component.hpp>

using namespace uth;

Component::Component()
	: m_active(false),
	  parent(nullptr)
{
}

Component::Component(std::string name)
	: m_name(name),
	  m_active(true),
	  parent(nullptr)
{
}

Component::~Component()
{
}

void Component::SetActive(bool active)
{
	m_active = active;
}

bool Component::GetActive()
{
	return m_active;
}

void Component::SetName(const std::string name)
{
	m_name = name;
}

const std::string Component::GetName() const
{
	return m_name;
}