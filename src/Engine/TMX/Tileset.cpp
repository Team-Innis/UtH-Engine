#include <UtH/Engine/TMX/Tileset.hpp>
#include <UtH/Platform/FileReader.h>

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
{ }

// Public


const Texture* Tileset::GetTexture() const
{
	return texture;
}

unsigned int Tileset::GetFirstGID() const
{
	return m_firstgid;
}


// Private


void Tileset::parseTileset(tinyxml2::XMLElement* tilesetElement, const std::string& mapFolder)
{
	m_firstgid = tilesetElement->UnsignedAttribute("firstgid");

	tinyxml2::XMLElement* imageElement = nullptr;

	const char* source = tilesetElement->Attribute("source");
	std::string path = mapFolder + source;
	if(source != 0)
	{
		// Open tsx file
		tinyxml2::XMLDocument doc;
		FileReader fr(path.c_str());
		doc.Parse(fr.ReadText(), fr.GetFileSize()+1);

		imageElement = doc.FirstChildElement("tileset")->FirstChildElement("image");
		WriteLog("%s", imageElement->ToText());
	}
	else
		imageElement = tilesetElement->FirstChildElement("image");

	std::string imagePath = mapFolder + imageElement->Attribute("source");
	texture = &uthRS.LoadTexture(imagePath);
}


// Local

tinyxml2::XMLElement* getImageElementFromTSX(const std::string& path)
{
	tinyxml2::XMLDocument doc;
	FileReader fr(path.c_str());

	// ReadText returns filesize+1 because of null termination
	doc.Parse(fr.ReadText(), fr.GetFileSize()+1);
	return doc.FirstChildElement("tileset")->FirstChildElement("image");
}