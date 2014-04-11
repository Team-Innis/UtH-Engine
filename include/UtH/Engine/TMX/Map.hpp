#pragma once
#ifndef MAP_TMX_UTH_H
#define MAP_TMX_UTH_H

#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/TMX/Enums.hpp>
#include <UtH/Engine/TMX/Tileset.hpp>

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

		private:
			//TODO: Add SpriteBatch
			std::vector<Tileset*> tilesets;

			Orientation::Orientation m_orientation;

			unsigned int m_width, m_height;
			unsigned int m_tileWidth, m_tileHeight;
		};
	}
}

#endif