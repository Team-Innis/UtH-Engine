#include <UtH/Platform/Android/InputController.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;


ControllerInput::ControllerInput()
    : m_buttons(Controller::BUTTON_COUNT, 1),
    m_prevButtons(Controller::BUTTON_COUNT, 1),
    m_hasChanged(false)
{ }

ControllerInput::~ControllerInput()
{ }


// Public


void ControllerInput::Initiate()
{
    Axis axis;

    axis.mappedAxis = AMOTION_EVENT_AXIS_HAT_X;
    m_axes.push_back(axis);
    axis.mappedAxis = AMOTION_EVENT_AXIS_HAT_Y;
    m_axes.push_back(axis);
    axis.mappedAxis = AMOTION_EVENT_AXIS_LTRIGGER;
    m_axes.push_back(axis);
    axis.mappedAxis = AMOTION_EVENT_AXIS_RTRIGGER;
    m_axes.push_back(axis);
    axis.mappedAxis = AMOTION_EVENT_AXIS_X;
    m_axes.push_back(axis);
    axis.mappedAxis = AMOTION_EVENT_AXIS_Y;
    m_axes.push_back(axis);
    axis.mappedAxis = AMOTION_EVENT_AXIS_Z;
    m_axes.push_back(axis);
    axis.mappedAxis = AMOTION_EVENT_AXIS_RZ;
    m_axes.push_back(axis);
}


void ControllerInput::Update()
{
    if (m_hasChanged)
    {
        m_prevButtons = m_buttons;
        m_hasChanged = false;
    }
}

bool ControllerInput::IsButtonDown(const Controller::Button button) const
{
    return m_buttons.at(button) == AKEY_EVENT_ACTION_DOWN;
}

bool ControllerInput::IsButtonUp(const Controller::Button button) const
{
    return !IsButtonDown(button);
}

bool ControllerInput::IsButtonPressed(const Controller::Button button) const
{
    return m_buttons.at(button) == AKEY_EVENT_ACTION_DOWN
        && m_prevButtons.at(button) == AKEY_EVENT_ACTION_UP;
}

bool ControllerInput::IsButtonReleased(const Controller::Button button) const
{
    return m_buttons.at(button) == AKEY_EVENT_ACTION_UP
        && m_prevButtons.at(button) == AKEY_EVENT_ACTION_DOWN;
}


float ControllerInput::GetAxis(const Controller::Axis axis, const float deadzone) const
{
    const float output = m_axes.at(axis).value;
    if (std::abs(output) <= deadzone)
        return 0;

    return output;
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
    m_hasChanged = true;
}

void ControllerInput::handleAxes(AInputEvent* inputEvent)
{
    for (int i = 0; i < m_axes.size(); ++i)
    {
        m_axes.at(i).update(inputEvent);
    }
}


ControllerInput::Axis::Axis()
    : mappedAxis(-1),
      value(0)
{ }


void ControllerInput::Axis::update(AInputEvent* inputEvent)
{
    value = AMotionEvent_getAxisValue(inputEvent, mappedAxis, 0);
}