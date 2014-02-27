#pragma once
#ifndef FILEREADER_H
#define FILEREADER_H

#include <UtH/Platform/Configuration.hpp>

#if defined(UTH_SYSTEM_ANDROID)
	#include <UtH/Platform/Android/FileReader.h>
#elif defined(UTH_SYSTEM_WINDOWS)
	#include <UtH/Platform/Win32/FileReader.h>
#else
	#error No filereader for such platform
#endif

#endif
