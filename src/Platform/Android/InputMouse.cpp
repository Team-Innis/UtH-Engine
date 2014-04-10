#include <UtH/Platform/Android/InputMouse.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

bool MouseInput::IsButtonDown(Mouse Button)
{
	WriteLog("No Mouse with android. Returning false");
	return false;
}
bool MouseInput::IsButtonPressed(Mouse Button)
{
	WriteLog("No Mouse with android. Returning false");
	return false;
}
bool MouseInput::IsButtonReleased(Mouse Button)
{
	WriteLog("No Mouse with android. Returning false");
	return false;
}

umath::vector2 MouseInput::MousePosition()
{
	WriteLog("No Mouse with android. Returning zero");
	return umath::vector2();
}
umath::vector2 MouseInput::MouseMovement()
{
	WriteLog("No Mouse with android. Returning zero");
	return umath::vector2();
}
void MouseInput::Update()
{

}