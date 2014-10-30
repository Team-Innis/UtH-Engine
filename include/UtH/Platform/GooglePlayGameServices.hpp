#include <UtH/Platform/Configuration.hpp>

#if defined(UTH_SYSTEM_ANDROID)
#include <UtH/Platform/Android/GooglePlayGameServices.hpp>
#elif defined(UTH_SYSTEM_WINDOWS) || defined(UTH_SYSTEM_LINUX)
#include <UtH/Platform/Common/GooglePlayGameServices.hpp>
#else
#error No GooglePlayGameServices for such platform
#endif