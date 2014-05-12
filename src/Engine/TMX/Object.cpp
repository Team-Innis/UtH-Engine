#include <UtH/Engine/TMX/Object.hpp>

#include <tinyxml2.h>

using namespace uth;
using namespace TMX;

Object::Object(tinyxml2::XMLElement* objectElement)
{
    parseObject(objectElement);
}

Object::~Object()
{ }


// Public

const umath::rectangle& Object::GetRectangle() const
{
	return m_rectangle;
}

const std::vector<umath::vector2>& Object::GetPoints() const
{
	return m_points;
}

const umath::vector2 Object::GetPosition() const
{
	return umath::vector2(m_rectangle.x, m_rectangle.y);
}

std::string Object::GetProperty(const std::string& name) const
{
	auto prop = m_properties.find(name);
	if(prop != m_properties.end())
		return prop->second;

	return std::string();
}

const std::string& Object::GetName() const
{
	return m_name;
}

const std::string& Object::GetType() const
{
	return m_typeString;
}

// Private

void Object::parseObject(tinyxml2::XMLElement* element)
{
    // Parse properties
    auto properties = element->FirstChildElement("properties");
    if(properties != nullptr)
    {
        parseProperties(properties);
    }

    // Parse actual object
}

void Object::parseProperties(tinyxml2::XMLElement* element)
{
    auto p = element->FirstChildElement("property");
	while(p != 0)
	{
		std::pair<std::string, std::string> tmp;
		tmp.first = p->Attribute("name");
		tmp.second = p->Attribute("value");

		m_properties.insert(tmp);

		p = p->NextSiblingElement("property");
	}
}
