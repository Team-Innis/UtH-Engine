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
