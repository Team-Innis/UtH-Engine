#pragma once
#ifndef TILESET_TMX_UTH_H
#define TILESET_TMX_UTH_H

#include <UtH/Resources/ResourceManager.h>
// For some "reason" you can't include this here
//#include <tinyxml2.h>
#include <string>

// Stupid hack to fix visual studio bugs
namespace tinyxml2
{
	class XMLElement;
}

namespace uth
{
	namespace TMX
	{
		class Tileset
		{
		public:
			Tileset(tinyxml2::XMLElement* tilesetElement, const std::string& mapFolder);
			 ~Tileset();

			const Texture* GetTexture() const;

			unsigned int GetFirstGID() const;
		private:
			void parseTileset(tinyxml2::XMLElement* tilesetElement, const std::string& mapFolder);

			unsigned int m_firstgid;

			unsigned int m_spacing, m_margin;

			Texture* m_texture;
		};
	}
}

#endif