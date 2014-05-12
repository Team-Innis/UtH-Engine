#pragma once
#ifndef OBJECT_TMX_UTH_H
#define OBJECT_TMX_UTH_H

#include <UtH/Math/Rectangle.hpp>
#include <UtH/Math/Vector2.hpp>

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
        class Object
        {
        public:
            Object(tinyxml2::XMLElement* objectElement);
            ~Object();

            const umath::rectangle& GetRectangle() const;
            const std::vector<umath::vector2>& GetPoints() const;

            std::string GetProperty(const std::string& name) const;

            const std::string& GetName() const;
            const std::string& GetType() const;

        private:
            void parseObject(tinyxml2::XMLElement* element);
            void parseProperties(tinyxml2::XMLElement* element);

            std::string m_name;
            std::string m_type;

            umath::rectangle m_rectangle;
            std::vector<umath::vector2> m_points;

			std::map<std::string, std::string> m_properties;
        };
    }
}

#endif