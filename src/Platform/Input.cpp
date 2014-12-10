#include <UtH/Platform/Input.hpp>
#include <UtH/Platform/JavaFunctions.hpp>

using namespace uth;

Input::Input()
	:f_androidBackButton([](){javaFunc::MoveTaskToBack(true); })
{
}
Input::~Input()
{}
void Input::SetWindow(void *windowHandle)
{
	InputBase::setWindowHandle(windowHandle);
	Mouse.Initiate();
	Keyboard.Initiate();
    Controller.Initiate();
}
void Input::Update(float deltaTime)
{
    Mouse.Update();
    Keyboard.Update();
    Touch.Update(deltaTime);
    Common.Update();
    Sensor.Update();
    Controller.Update();
}
void Input::SetAndroidBackFunction(std::function<void()> function)
{
	f_androidBackButton = function;
}

void Input::RunBackButton()
{
	f_androidBackButton();
}