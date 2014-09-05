#include <UtH/Platform/Android/InputMouse.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

bool MouseInput::IsButtonDown(Mouse)
{
	WriteLog("No Mouse with android. Returning false");
	return false;
}
bool MouseInput::IsButtonPressed(Mouse)
{
	WriteLog("No Mouse with android. Returning false");
	return false;
}
bool MouseInput::IsButtonReleased(Mouse)
{
	WriteLog("No Mouse with android. Returning false");
	return false;
}

pmath::Vec2 MouseInput::Position()
{
	WriteLog("No Mouse with android. Returning zero");
	return pmath::Vec2();
}
pmath::Vec2 MouseInput::Movement()
{
	WriteLog("No Mouse with android. Returning zero");
	return pmath::Vec2();
}
pmath::Vec2 MouseInput::Wheel()
{
	WriteLog("No Mouse with android. Returning zero");
	return pmath::Vec2();
}