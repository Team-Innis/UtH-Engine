#include <UtH/Engine/TMX/Tile.hpp>

using namespace uth;
using namespace TMX;

Tile::Tile()
{ }

Tile::Tile(const pmath::Rect& tile)
{
	tileRectangle = tile;
	transform.SetPosition(tile.position.x, tile.position.y);
	transform.setSize(tile.size.x, tile.size.y);
	transform.SetOrigin(Origin::TopLeft);
}


Tile::~Tile()
{ }