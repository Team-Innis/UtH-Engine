#pragma once
#ifndef TILE_TMX_UTH_H
#define TILE_TMX_UTH_H

#include <UtH/Math/Rectangle.hpp>
#include <UtH/Engine/GameObject.hpp>

namespace uth
{
	namespace TMX
	{
		class Tile : public GameObject
		{
		public:
			Tile();
			Tile(const umath::rectangle& tile);
			~Tile();

			umath::rectangle tileRectangle;
		};
	}
}

#endif