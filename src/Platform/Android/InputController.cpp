#include <UtH/Platform/Android/InputController.hpp>

using namespace uth;


ControllerInput::ControllerInput()
    : m_buttons(Controller::BUTTON_COUNT, false),
      m_PrevButtons(Controller::BUTTON_COUNT, false)
{ }

ControllerInput::~ControllerInput()
{ }


// Public

void ControllerInput::Update()
{
    m_PrevButtons = m_buttons;
}

bool ControllerInput::IsButtonDown(Controller::Button button)
{
    return m_buttons.at(button);
}

bool ControllerInput::IsButtonUp(Controller::Button button)
{
    return !IsButtonDown(button);
}

bool ControllerInput::IsButtonPressed(Controller::Button button)
{
    return false;
}

bool ControllerInput::IsButtonReleased(Controller::Button button)
{
    return false;
}

void ControllerInput::HandleInput(AInputEvent* inputEvent)
{
    switch (AInputEvent_getType(inputEvent))
    {
    case AINPUT_EVENT_TYPE_KEY:
        handleKeys(inputEvent);
        break;
    case AINPUT_EVENT_TYPE_MOTION:
        handleAxes(inputEvent);
        break;
    }
}


// Private
void ControllerInput::handleKeys(AInputEvent* inputEvent)
{

}

void ControllerInput::handleAxes(AInputEvent* inputEvent)
{

}
