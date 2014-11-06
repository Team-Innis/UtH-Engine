#include <UtH/Engine/TMX/Map.hpp>
#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Debug.hpp>

#include <tinyxml2.h>
#include <cassert>

using namespace uth;
using namespace TMX;

Orientation::Orientation getOrientation(const std::string& value);

Map::Map()
{ }

Map::Map(const std::string& path)
{
	LoadFromFile(path);
}

Map::~Map()
{
    tilesets.clear();
    layers.clear();
    objectGroups.clear();
}

bool Map::LoadFromFile(const std::string& path)
{
	// Create the xml document
	tinyxml2::XMLDocument doc;
	FileManager fr(path.c_str());
    doc.Parse(fr.ReadText().c_str());

	// Parse the map element
	tinyxml2::XMLElement* map = doc.FirstChildElement("map");
    if (map == nullptr)
    {
        WriteError("Could not open map from path: %s", path.c_str());
        assert(false);
    }

	m_orientation = getOrientation(map->Attribute("orientation"));
    if (m_orientation != Orientation::ORTHOGONAL)
    {
        WriteError("Only orthogonal maps are supported");
        assert(false);
    }
	m_width = map->UnsignedAttribute("width");
	m_height = map->UnsignedAttribute("height");
	m_tileWidth = map->UnsignedAttribute("tilewidth");
	m_tileHeight = map->UnsignedAttribute("tileheight");

	
	// Parse tilesets
	auto tileset = map->FirstChildElement("tileset");
	while(tileset != 0)
	{
		std::string mapfolder = path.substr(0, path.find_last_of("/")+1);
		tilesets.emplace_back(new Tileset(tileset, mapfolder));
		tileset = tileset->NextSiblingElement("tileset");
	}

	// Parse layers
	auto layer = map->FirstChildElement("layer");
	while(layer != 0)
	{
		layers.emplace_back(new TileLayer(layer, this));
		layer = layer->NextSiblingElement("layer");
	}

	// Parse objectgroups
	auto objectgroup = map->FirstChildElement("objectgroup");
	while(objectgroup != 0)
	{
		objectGroups.emplace_back(new ObjectGroup(objectgroup));
		objectgroup = objectgroup->NextSiblingElement("objectgroup");
	}

	return true;
}

unsigned int Map::GetWidth() const
{
	return m_width;
}

unsigned int Map::GetTileWidth() const
{
	return m_tileWidth;
}

unsigned int Map::GetHeight() const
{
	return m_height;
}

unsigned int Map::GetTileHeight() const
{
	return m_tileHeight;
}

TileLayer* Map::GetLayer(const std::string& name)
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		auto layer = it->get();
		if(layer->GetName() == name)
			return layer;
	}

	return nullptr;
}

ObjectGroup* Map::GetObjectGroup(const std::string& name)
{
    for (auto it = objectGroups.begin(); it != objectGroups.end(); ++it)
    {
        auto objectgroup = it->get();
        if (objectgroup->GetName() == name)
            return objectgroup;
    }

    return nullptr;
}


// Private

void Map::draw(RenderTarget& target)
{
	for(auto it = layers.begin(); it != layers.end(); ++it)
		(*it)->Draw(target);
}

// Local

Orientation::Orientation getOrientation(const std::string& value)
{
	if(value == "orthogonal")
		return Orientation::ORTHOGONAL;
	else if(value == "isometric")
		return Orientation::ISOMETRIC;
	else if(value == "staggered")
		return Orientation::STAGGERED;

	return Orientation::UNKNOWN;
}