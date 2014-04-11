#pragma once
#ifndef TILE_TMX_UTH_H
#define TILE_TMX_UTH_H

#include <UtH/Engine/GameObject.hpp>

namespace uth
{
	namespace TMX
	{
		class Tile : public GameObject
		{
		public:
			int GetGID() const
			{
				return m_gid;
			}
		private:
			int m_gid;
		};
	}
}

#endif