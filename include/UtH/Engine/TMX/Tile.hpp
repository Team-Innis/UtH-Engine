#pragma once
#ifndef TILE_TMX_UTH_H
#define TILE_TMX_UTH_H

#include <pmath/Rectangle.hpp>
#include <UtH/Engine/GameObject.hpp>

namespace uth
{
	namespace TMX
	{
		class Tile : public GameObject
		{
		public:
			Tile();
			Tile(const pmath::Rect& tile);
			~Tile();

			pmath::Rect tileRectangle;
		};
	}
}

#endif