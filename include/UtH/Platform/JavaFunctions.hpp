#include <UtH/Platform/Configuration.hpp>

#if defined(UTH_SYSTEM_ANDROID)
#include <UtH/Platform/Android/JavaFunctions.hpp>
#elif defined(UTH_SYSTEM_WINDOWS) || defined(UTH_SYSTEM_LINUX)
#include <UtH/Platform/Common/JavaFunctions.hpp>
#else
#error No JavaFunctions for such platform
#endif