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
}
void Input::Update()
{
	Mouse.Update();
	Touch.Update();
}
