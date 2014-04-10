#include <UtH/Platform/Android/InputMouse.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

bool MouseInput::IsButtonDown(Mouse Button)
{
	WriteError("No Mouse with android. Returning false");
	return false;
}
bool MouseInput::IsButtonPressed(Mouse Button)
{
	WriteError("No Mouse with android. Returning false");
	return false;
}
bool MouseInput::IsButtonReleased(Mouse Button)
{
	WriteError("No Mouse with android. Returning false");
	return false;
}

umath::vector2 MouseInput::MousePosition()
{
	WriteError("No Mouse with android. Returning zero");
	return umath::vector2();
}
umath::vector2 MouseInput::MouseMovement()
{
	WriteError("No Mouse with android. Returning zero");
	return umath::vector2();
}
void MouseInput::Update()
{

}