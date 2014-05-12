#pragma once
#ifndef OBJECTGROUP_TMX_UTH_H
#define OBJECTGROUP_TMX_UTH_H

#include <UtH/Engine/TMX/Object.hpp>

#include <vector>
#include <map>
#include <string>

// Forward declaration
namespace tinyxml2
{
	class XMLElement;
}

namespace uth
{
    namespace TMX
    {
        class ObjectGroup
        {
        public:
            typedef std::vector<Object*> ObjectList;

            ObjectGroup(tinyxml2::XMLElement* objectGroupElement);
            ~ObjectGroup();

            const Object* GetObject(const std::string& name) const;

            const ObjectList* GetObjectsByType(const std::string& type) const;

            std::string GetProperty(const std::string& name) const;

            const std::string& GetName() const;
            
            unsigned int GetWidth() const;
            unsigned int GetHeight() const;
        private:
            void parseObjectGroup(tinyxml2::XMLElement* element);
            void parseProperties(tinyxml2::XMLElement* element);

            std::string m_name;
            unsigned int m_width, m_height;
            
            // Objects by name
            std::map<std::string, Object*> m_objects;
            // Objects by type
            std::map<std::string, ObjectList> m_types;

			std::map<std::string, std::string> m_properties;
        };
    }
}

#endif