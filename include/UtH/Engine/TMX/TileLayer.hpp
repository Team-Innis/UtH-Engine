#pragma once
#ifndef LAYER_TMX_UTH_H
#define LAYER_TMX_UTH_H

#include <UtH/Engine/TMX/Tile.hpp>
#include <UtH/Engine/TMX/TileHackBatch.hpp>

#include <string>
#include <vector>
#include <map>

// Forward declaration
namespace tinyxml2
{
	class XMLElement;
}

namespace uth
{
	namespace TMX
	{
		class Map;

		class TileLayer
		{
		public:
			TileLayer(tinyxml2::XMLElement* layerElement, Map* map);
			 ~TileLayer();

			void Draw(RenderTarget& target);

			const std::string& GetName();

			unsigned int GetHeight();
			unsigned int GetWidth();

			std::string GetProperty(const std::string& name);

			Tile* GetTile(const int x, const int y);
		private:
			void parseElement(tinyxml2::XMLElement* layerElement, Map* map);
			void parseProperties(tinyxml2::XMLElement* propertiesElement);

			std::string m_name;

			unsigned int m_width, m_height;

			std::vector<Tile*> m_tiles;

			std::map<std::string, std::string> m_properties;
			std::map<Texture*, SpriteBatch*> m_spriteBatches;
		};
	}
}

#endif