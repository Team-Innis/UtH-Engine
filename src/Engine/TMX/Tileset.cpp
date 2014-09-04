#include <UtH/Engine/TMX/Tileset.hpp>
#include <UtH/Engine/TMX/Map.hpp>
#include <UtH/Platform/FileReader.h>

#include <UtH/Platform/Debug.hpp>

// Works fine here
#include <tinyxml2.h>


using namespace uth;
using namespace TMX;

// map might use a .tsx tileset file.
// the actual tileset image needs to be read from the file
tinyxml2::XMLElement* getImageElementFromTSX(const std::string& path);


Tileset::Tileset(tinyxml2::XMLElement* tilesetElement, const std::string& mapFolder)
{
	parseTileset(tilesetElement, mapFolder);
}

Tileset::~Tileset()
{
	m_texture = nullptr;
}

// Public


Texture* Tileset::GetTexture() const
{
	return m_texture;
}

unsigned int Tileset::GetFirstGID() const
{
	return m_firstgid;
}

unsigned int Tileset::GetTileWidth() const
{
	return m_tileWidth;
}

unsigned int Tileset::GetTileHeight() const
{
	return m_tileHeight;
}

const umath::rectangle Tileset::GetTile(unsigned int localId) const
{
	const unsigned int wTiles = static_cast<unsigned int>(m_texture->GetSize().x) / m_tileWidth;
    const unsigned int hTiles = static_cast<unsigned int>(m_texture->GetSize().y) / m_tileHeight;

	int x = localId % wTiles * m_tileWidth;
	int y = localId / wTiles * m_tileHeight;

	const int xtile = x / m_tileWidth;
	const int ytile = y / m_tileHeight;

	x += m_margin;
	y += m_margin;

	x += xtile * m_spacing;
	y += ytile * m_spacing;

	umath::rectangle out;
	out.x = x / m_texture->GetSize().x;
	out.width = m_tileWidth / m_texture->GetSize().x;
	out.y = y / m_texture->GetSize().y;
	out.height = m_tileHeight / m_texture->GetSize().y;

	return out;
}



// Private


void Tileset::parseTileset(tinyxml2::XMLElement* tilesetElement, const std::string& mapFolder)
{
	// In case the tileset is in a .tsx file
	tinyxml2::XMLDocument doc;

	m_firstgid = tilesetElement->UnsignedAttribute("firstgid");

	tinyxml2::XMLElement* imageElement = nullptr;

	const char* tilesetSource = tilesetElement->Attribute("source");
	// If tileset has a source attribute then the tileset is defined in a .tsx file
	if(tilesetSource != 0)
	{
		// Open tsx file
		std::string path = mapFolder + tilesetSource;
		FileReader fr(path.c_str());
		doc.Parse(fr.ReadText().c_str());

		auto tileset = doc.FirstChildElement("tileset");

		m_tileWidth = tileset->UnsignedAttribute("tilewidth");
		m_tileHeight = tileset->UnsignedAttribute("tileheight");
		m_spacing = tileset->UnsignedAttribute("spacing");
		m_margin = tileset->UnsignedAttribute("margin");

		imageElement = tileset->FirstChildElement("image");
	}
	else
	{
		m_tileWidth = tilesetElement->UnsignedAttribute("tilewidth");
		m_tileHeight = tilesetElement->UnsignedAttribute("tileheight");
		m_spacing = tilesetElement->UnsignedAttribute("spacing");
		m_margin = tilesetElement->UnsignedAttribute("margin");

		imageElement = tilesetElement->FirstChildElement("image");
	}


	std::string imagePath = mapFolder + imageElement->Attribute("source");

	std::string temp = imagePath.substr(imagePath.length() - 4, 4);
	if (temp == ".png")
	{
		std::string warn;
		warn.reserve(250);
		warn.append("Warning: TMX mapfile uses file ");
		warn.append(imagePath);
		warn.append("\nUTH Engine does not support png files\nSearching for tga file with the same file name");

		WriteWarning(warn.c_str());

		imagePath.replace(imagePath.length() - 4, 4,".tga");
	}

	m_texture = uthRS.LoadTexture(imagePath);
}


// Local

tinyxml2::XMLElement* getImageElementFromTSX(const std::string& path)
{
	tinyxml2::XMLDocument doc;
	FileReader fr(path.c_str());

	// ReadText returns filesize+1 because of null termination
	doc.Parse(fr.ReadText().c_str());
	return doc.FirstChildElement("tileset")->FirstChildElement("image");
}