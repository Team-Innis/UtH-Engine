#include <UtH/Engine/TMX/Map.hpp>
#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>

#include <tinyxml2.h>

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
	for(auto it = tilesets.begin(); it != tilesets.end(); ++it)
		delete (*it);
	tilesets.clear();
}

bool Map::LoadFromFile(const std::string& path)
{
	// Create the xml document
	tinyxml2::XMLDocument doc;
	FileReader fr(path.c_str());
	doc.Parse(fr.ReadText().c_str());

	// Parse the map element
	tinyxml2::XMLElement* map = doc.FirstChildElement("map");
	m_orientation = getOrientation(map->Attribute("orientation"));
	assert(m_orientation == Orientation::ORTHOGONAL);
	m_width = map->UnsignedAttribute("width");
	m_height = map->UnsignedAttribute("height");
	m_tileWidth = map->UnsignedAttribute("tilewidth");
	m_tileHeight = map->UnsignedAttribute("tileheight");

	
	// Parse tilesets
	auto tileset = map->FirstChildElement("tileset");
	while(tileset != 0)
	{
		// TODO: Make getting the map folder better
		std::string mapfolder = path.substr(0, path.find_last_of("/")+1);
		tilesets.push_back(new Tileset(tileset, mapfolder));
		tileset = map->NextSiblingElement("tileset");
	}

	// Parse layers


	// Parse objectgroups

	return true;
}


// Private

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