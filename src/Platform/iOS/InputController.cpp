#include <UtH/Platform/iOS/InputController.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

ControllerInput::ControllerInput()
{ }

ControllerInput::~ControllerInput()
{ }


// Public

void ControllerInput::Update()
{
    
}

bool ControllerInput::IsButtonDown(const Controller::Button button) const
{
    WriteLog("Not supported on iOS");
    return false;
}

bool ControllerInput::IsButtonUp(const Controller::Button button) const
{
    WriteLog("Not supported on iOS");
    return false;
}

bool ControllerInput::IsButtonPressed(const Controller::Button button) const
{
    WriteLog("Not supported on iOS");
    return false;
}

bool ControllerInput::IsButtonReleased(const Controller::Button button) const
{
    WriteLog("Not supported on iOS");
    return false;
}

float ControllerInput::GetAxis(const Controller::Axis axis, float deadzone) const
{
    WriteLog("Not supported on iOS");
    return 0;
}