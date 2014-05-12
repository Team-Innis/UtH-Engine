#pragma once
#ifndef MAP_TMX_UTH_H
#define MAP_TMX_UTH_H

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Engine/TMX/Enums.hpp>
#include <UtH/Engine/TMX/Tileset.hpp>
#include <UtH/Engine/TMX/TileLayer.hpp>
#include <UtH/Engine/TMX/ObjectGroup.hpp>

#include <string>
#include <vector>

namespace uth
{
	namespace TMX
	{
		class Map : public GameObject
		{
		public:
			Map();
			Map(const std::string& path);
			~Map();
			bool LoadFromFile(const std::string& path);

			unsigned int GetWidth() const;
			unsigned int GetTileWidth() const;
			unsigned int GetHeight() const;
			unsigned int GetTileHeight() const;

			TileLayer* GetLayer(const std::string& name);

			std::vector<Tileset*> tilesets;
			std::vector<TileLayer*> layers;
			std::vector<ObjectGroup*> objectGroups;
		private:
			void draw(RenderTarget& target);

			Orientation::Orientation m_orientation;

			unsigned int m_width, m_height;
			unsigned int m_tileWidth, m_tileHeight;
		};
	}
}

#endif