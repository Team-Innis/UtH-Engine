#include <UtH/Platform/Common/InputController.hpp>

using namespace uth;


ControllerInput::ControllerInput()
{ }

ControllerInput::~ControllerInput()
{ }


// Public

bool ControllerInput::IsButtonDown(Controller::Button /*button*/)
{
    return false;
}

bool ControllerInput::IsButtonUp(Controller::Button /*button*/)
{
    return false;
}

bool ControllerInput::IsButtonPressed(Controller::Button /*button*/)
{
    return false;
}

bool ControllerInput::IsButtonReleased(Controller::Button /*button*/)
{
    return false;
}