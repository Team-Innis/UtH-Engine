#pragma once
#ifndef RESOURCE_H_UTH
#define RESOURCE_H_UTH

#include <string>
#include <UtH/Platform/Uncopyable.hpp>

namespace uth
{
	class Resource : private Uncopyable
	{
		friend class ResourceManager;
	public:
		Resource();
		virtual bool IsLoaded() const;

	protected:

		virtual bool LoadFromFile(const std::string& filePath) = 0;
		virtual void Unload() = 0;
		virtual bool EnsureLoaded();

		bool m_loaded;
	};
}

#endif //RESOURCE_H_UTH
