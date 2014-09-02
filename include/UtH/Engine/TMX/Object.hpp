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
			enum Type
			{
				NONE = 0,
				RECTANGLE,
				POLYGON,
				LINE
			};

            Object(tinyxml2::XMLElement* objectElement);
            ~Object();

            const umath::rectangle& GetRectangle() const;
			// Returns the points for polygon and line
            const std::vector<umath::vector2>& GetPoints() const;
			// Return the position of the object
			// Is also the start position for line and polygon
			const umath::vector2 GetPosition() const;

            std::string GetProperty(const std::string& name) const;

            const std::string& GetName() const;
            const std::string& GetType() const;

        private:
            void parseObject(tinyxml2::XMLElement* element);
            void parseProperties(tinyxml2::XMLElement* element);
			void parsePoints(const std::string& points);

			Type m_type;

            std::string m_name;
            std::string m_typeString;

            umath::rectangle m_rectangle;
            std::vector<umath::vector2> m_points;

			std::map<std::string, std::string> m_properties;
        };
    }
}

#endif