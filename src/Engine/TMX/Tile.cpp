#include <UtH/Engine/TMX/Tile.hpp>

using namespace uth;
using namespace TMX;

Tile::Tile()
{ }

Tile::Tile(const umath::rectangle& tile)
{
	transform.SetPosition(tile.x, tile.y);
	transform.SetSize(tile.width, tile.height);
}


Tile::~Tile()
{ }