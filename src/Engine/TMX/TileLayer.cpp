#include <UtH/Engine/TMX/TileLayer.hpp>
#include <UtH/Engine/TMX/Map.hpp>
#include <pmath/Rectangle.hpp>

#include <tinyxml2.h>

// Bits on the far end of the 32-bit global tile ID are used for tile flags
const unsigned int FLIPPED_HORIZONTALLY_FLAG    = 0x80000000;
const unsigned int FLIPPED_VERTICALLY_FLAG      = 0x40000000;
const unsigned int FLIPPED_DIAGONALLY_FLAG      = 0x20000000;


using namespace uth;
using namespace TMX;

TileLayer::TileLayer(tinyxml2::XMLElement* layerElement, Map* map)
{
	for(auto it = map->tilesets.begin(); it != map->tilesets.end(); ++it)
	{
		Texture* t = (*it)->GetTexture();

		if(m_spriteBatches.find(t) == m_spriteBatches.end())
		{
            auto s = new SpriteBatch(false);
			s->SetTexture(t);
			m_spriteBatches[t] = s;
		}
	}

	parseElement(layerElement, map);
}

TileLayer::~TileLayer()
{
	for(auto it = m_tiles.begin(); it != m_tiles.end(); ++it)
		delete (*it);

	for(auto it = m_spriteBatches.begin(); it != m_spriteBatches.end(); ++it)
		delete (*it).second;
}


// Public

void TileLayer::Draw(RenderTarget& target)
{
    if (!m_active)
        return;

	for(auto it = m_spriteBatches.begin(); it != m_spriteBatches.end(); ++it)
		(*it).second->Draw(target);
}

unsigned int TileLayer::GetHeight()
{
	return m_height;
}

unsigned int TileLayer::GetWidth()
{
	return m_width;
}

const std::string& TileLayer::GetName()
{
	return m_name;
}

std::string TileLayer::GetProperty(const std::string& name)
{
	auto result = m_properties.find(name);
	if(result != m_properties.end())
		return result->second;

	return std::string();
}

Tile* TileLayer::GetTile(const int x, const int y)
{
	for(auto it = m_tiles.begin(); it != m_tiles.end(); ++it)
	{
		auto tile = (*it);
		if(tile->tileRectangle.position.x == x && tile->tileRectangle.position.y == y)
			return tile;
	}
	
	return nullptr;
}

// Private

void TileLayer::parseElement(tinyxml2::XMLElement* layerElement, Map* map)
{
	// Get properties
	auto properties = layerElement->FirstChildElement("properties");
	if(properties != 0)
		parseProperties(properties);

	m_name = layerElement->Attribute("name");
	m_width = layerElement->UnsignedAttribute("width");
	m_height = layerElement->UnsignedAttribute("height");
    if (layerElement->Attribute("visible") != 0)
    {
        m_active = layerElement->IntAttribute("visible") == 0 ? false : true;
    }
    else
        m_active = true;

	// Parse data
	unsigned int x = 0;
	unsigned int y = 0;
	auto tile = layerElement->FirstChildElement("data")->FirstChildElement("tile");
	while(tile != 0)
	{
		unsigned int gid = tile->UnsignedAttribute("gid");

        // Go to the next "line"
        if (x >= map->GetWidth())
        {
            x = 0;
            y++;
        }

        // Tile is "empty space"
        if (gid == 0)
        {
            x++;
            tile = tile->NextSiblingElement("tile");
            continue;
        }

		// Read out the flags
		bool flipped_horizontally = (gid & FLIPPED_HORIZONTALLY_FLAG) != 0;
		bool flipped_vertically = (gid & FLIPPED_VERTICALLY_FLAG) != 0;
        // TODO: implement this
		//bool flipped_diagonally = (gid & FLIPPED_DIAGONALLY_FLAG) != 0;

		// Clear the flags
		gid &= ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG
			| FLIPPED_DIAGONALLY_FLAG);

		// Find correct tileset
		for(int i = map->tilesets.size() - 1; i >= 0; --i)
		{
			Tileset* tileset = map->tilesets[i].get();

            if (tileset->GetFirstGID() <= gid)
            {
                const pmath::Rect t(static_cast<float>(x * tileset->GetTileWidth()), static_cast<float>(y * tileset->GetTileHeight()),
                    static_cast<float>(tileset->GetTileWidth()), static_cast<float>(tileset->GetTileHeight()));

                auto tile = new Tile(t);

                // NOTE: do diagonal before these
                if (flipped_horizontally)
                    tile->transform.SetScale(-1, tile->transform.GetScale().y);
                if (flipped_vertically)
                    tile->transform.SetScale(tile->transform.GetScale().x, -1);

                tile->parent = static_cast<GameObject*>(map);
                const pmath::Rect texCoords = tileset->GetTile(gid - tileset->GetFirstGID());

                m_tiles.push_back(tile);
                m_spriteBatches.at(tileset->GetTexture())->AddSprite(&tile->transform, "", pmath::Vec4(1, 1, 1, 1), texCoords);
                x++;
                break;
            }
		}
		tile = tile->NextSiblingElement("tile");
	}
}

void TileLayer::parseProperties(tinyxml2::XMLElement* propertiesElement)
{
	auto p = propertiesElement->FirstChildElement("property");
	while(p != 0)
	{
		std::pair<std::string, std::string> tmp;
		tmp.first = p->Attribute("name");
		tmp.second = p->Attribute("value");

		m_properties.insert(tmp);

		p = p->NextSiblingElement("property");
	}
}