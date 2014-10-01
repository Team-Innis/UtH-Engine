#include <UtH/Platform/Common/JavaFunctions.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

JavaFunctions::JavaFunctions(){}

JavaFunctions::~JavaFunctions(){}

void JavaFunctions::Vibrate(int time_ms)
{
	WriteLog("\nNo JavaFunctions outside of Android.\n");
}