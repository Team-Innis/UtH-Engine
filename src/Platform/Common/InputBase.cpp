#include <UtH/Platform/Common/InputBase.hpp>

using namespace uth;

void* InputBase::windowHandle = nullptr;

void InputBase::setWindowHandle(void* WindowHandle)
{
	windowHandle = WindowHandle;
}
