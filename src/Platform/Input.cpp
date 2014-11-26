#include <UtH/Platform/Input.hpp>

using namespace uth;

Input::Input()
    : m_handleBackButton(false)
{}
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
    if (function)
    {
        f_androidBackButton = function;
        m_handleBackButton = true;
    }
    else
    {
        m_handleBackButton = false;
    }
}

bool Input::RunBackButton()
{
    if (m_handleBackButton)
        f_androidBackButton();

    return m_handleBackButton;
}