#include <UtH/Platform/Input.hpp>

using namespace uth;

Input::Input()
{}
Input::~Input()
{}
void Input::SetWindow(void *windowHandle)
{
	InputBase::setWindowHandle(windowHandle);
	Mouse.Initiate();
	Keyboard.Initiate();
}
void Input::Update(float deltaTime)
{
    Mouse.Update();
    Keyboard.Update();
    Touch.Update(deltaTime);
    Common.Update();
    Sensor.Update();
}