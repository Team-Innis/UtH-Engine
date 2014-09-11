#include <UtH/Platform/Android/InputController.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;


ControllerInput::ControllerInput()
    : m_buttons(Controller::BUTTON_COUNT, 1),
      m_prevButtons(Controller::BUTTON_COUNT, 1)
{ }

ControllerInput::~ControllerInput()
{ }


// Public

void ControllerInput::Update()
{
    m_prevButtons = m_buttons;
}

bool ControllerInput::IsButtonDown(Controller::Button button)
{
    return m_buttons.at(button) == AKEY_EVENT_ACTION_DOWN;
}

bool ControllerInput::IsButtonUp(Controller::Button button)
{
    return !IsButtonDown(button);
}

bool ControllerInput::IsButtonPressed(Controller::Button button)
{
    return m_buttons.at(button) == AKEY_EVENT_ACTION_DOWN
        && m_prevButtons.at(button) == AKEY_EVENT_ACTION_UP;
}

bool ControllerInput::IsButtonReleased(Controller::Button button)
{
    return m_buttons.at(button) == AKEY_EVENT_ACTION_UP
        && m_prevButtons.at(button) == AKEY_EVENT_ACTION_DOWN;
}

void ControllerInput::HandleInput(AInputEvent* inputEvent)
{
    if (AInputEvent_getType(inputEvent) == AINPUT_EVENT_TYPE_KEY)
        handleKeys(inputEvent);
    else
        handleAxes(inputEvent);
}


// Private
void ControllerInput::handleKeys(AInputEvent* inputEvent)
{
    int button;

    switch (AKeyEvent_getKeyCode(inputEvent))
    {
    case AKEYCODE_BUTTON_A:
        button = Controller::ButtonA;
        break;
    case AKEYCODE_BUTTON_B:
        button = Controller::ButtonB;
        break;
    case AKEYCODE_BUTTON_X:
        button = Controller::ButtonX;
        break;
    case AKEYCODE_BUTTON_Y:
        button = Controller::ButtonY;
        break;
    case AKEYCODE_BUTTON_SELECT:
        button = Controller::Select;
        break;
    case AKEYCODE_BUTTON_START:
        button = Controller::Start;
        break;
    case AKEYCODE_DPAD_UP:
        button = Controller::DpadUp;
        break;
    case AKEYCODE_DPAD_LEFT:
        button = Controller::DpadLeft;
        break;
    case AKEYCODE_DPAD_RIGHT:
        button = Controller::DpadRight;
        break;
    case AKEYCODE_DPAD_DOWN:
        button = Controller::DpadDown;
        break;
    case AKEYCODE_BUTTON_L1:
        button = Controller::L1;
        break;
    case AKEYCODE_BUTTON_R1:
        button = Controller::R1;
        break;
    case AKEYCODE_BUTTON_THUMBL:
        button = Controller::ThumbLeft;
        break;
    case AKEYCODE_BUTTON_THUMBR:
        button = Controller::ThumbRight;
        break;
    default:
        button = -1;
        break;
    }

    if (button == -1)
        return;

    int action = AKeyEvent_getAction(inputEvent);
    m_buttons.at(button) = action;
}

void ControllerInput::handleAxes(AInputEvent* inputEvent)
{

}
