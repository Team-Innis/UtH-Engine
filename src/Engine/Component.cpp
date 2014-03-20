#include <UtH/Engine/Component.hpp>

using namespace uth;

Component::Component()
	: m_active(false),
	  m_draw(false),
	  m_dynamic(false),
	  parent(nullptr)
{
}

Component::Component(std::string name)
	: m_name(name),
	  m_active(true),
	  m_draw(false),
	  m_dynamic(false),
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

void Component::SetDrawable(bool drawable)
{
	m_draw = drawable;
}

bool Component::GetDrawable()
{
	return m_draw;
}

void Component::SetDynamic(bool dynamic)
{
	m_dynamic = dynamic;
}

bool Component::GetDynamic()
{
	return m_dynamic;
}

void Component::SetName(const std::string name)
{
	m_name = name;
}

const std::string Component::GetName() const
{
	return m_name;
}