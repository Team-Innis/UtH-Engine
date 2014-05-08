#pragma once
#ifndef TILEHACK_UTH_H
#define TILEHACK_UTH_H

#include <UtH/Engine/SpriteBatch.hpp>

namespace uth
{
	namespace TMX
	{
		class TileHackBatch : public SpriteBatch
		{
		public:
			TileHackBatch(const bool adoptPointers = true);
			~TileHackBatch();
		private:
			void draw(RenderTarget& target);
		};
	}
}

#endif