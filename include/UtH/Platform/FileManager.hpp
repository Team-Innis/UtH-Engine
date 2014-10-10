#include <UtH/Platform/Configuration.hpp>

#if defined(UTH_SYSTEM_ANDROID)
	#include <UtH/Platform/Android/FileManager.hpp>
#elif defined(UTH_SYSTEM_WINDOWS) || defined(UTH_SYSTEM_LINUX)
	#include <UtH/Platform/Common/FileManager.hpp>
#else
	#error No filereader for such platform
#endif