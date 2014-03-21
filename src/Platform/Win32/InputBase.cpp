#include <UtH/Platform/Win32/InputBase.hpp>
#include <GLFW/glfw3.h>

using namespace uth;

void* InputBase::windowHandle = nullptr;

void InputBase::setWindowHandle(void* WindowHandle)
{
	windowHandle = WindowHandle;
}
