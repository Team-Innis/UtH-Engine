#include <UtH/Platform/Common/InputController.hpp>
#include <UtH/Platform/Debug.hpp>
#include <GLFW/glfw3.h>

using namespace uth;

namespace
{
    enum glfwAxis
    {
        LeftThumbX,
        LeftThumbY,
        Trigger,
        RightThumbY,
        RightThumbX,
        AXIS_COUNT
    };
}


ControllerInput::ControllerInput()
    : m_buttons(Controller::BUTTON_COUNT, 0),
      m_prevButtons(Controller::BUTTON_COUNT, 0),
      m_axes(Controller::AXIS_COUNT, 0)
{ }

ControllerInput::~ControllerInput()
{ }


// Public

void ControllerInput::Update()
{
    // Check just in case because controller might vanish during gameplay
    if (glfwJoystickPresent(0))
    {
        m_prevButtons = m_buttons;

        int buttonCount;
        auto buttons = glfwGetJoystickButtons(0, &buttonCount);
        for (int i = 0; i < buttonCount && i < m_buttons.size(); ++i)
            m_buttons.at(i) = buttons[i];

        int axisCount;
        auto axes = glfwGetJoystickAxes(0, &axisCount);
        for (int i = 0; i < axisCount && m_axes.size(); ++i)
        {
            m_axes.at(i) = axes[i];
        }
    }
}

bool ControllerInput::IsButtonDown(const Controller::Button button) const
{
    return m_buttons.at(button) != 0;
}

bool ControllerInput::IsButtonUp(const Controller::Button button) const
{
    return !IsButtonDown(button);
}

bool ControllerInput::IsButtonPressed(const Controller::Button button) const
{
    return m_buttons.at(button) != 0 && m_prevButtons.at(button) == 0;
}

bool ControllerInput::IsButtonReleased(const Controller::Button button) const
{
    return m_buttons.at(button) == 0 && m_prevButtons.at(button) != 0;
}

float ControllerInput::GetAxis(const Controller::Axis axis, float deadzone) const
{
    float output = 0;

    switch (axis)
    {
        // dpad axises don't seem to exist on windows so just return
    case Controller::DpadX:
        return 0;
        break;
    case Controller::DpadY:
        return 0;
        break;
    case Controller::LeftTrigger:
        if (m_axes.at(Trigger) >= 0)
            output =  m_axes.at(Trigger);
        else
            return 0; // can just return in this case
        break;
    case Controller::RightTrigger:
        if (m_axes.at(Trigger) <= 0)
            output = std::abs(m_axes.at(Trigger));
        else
            return 0; // can just return in this case
        break;
    case Controller::LeftThumbX:
        output = m_axes.at(LeftThumbX);
        break;
    case Controller::LeftThumbY:
        output = m_axes.at(LeftThumbY);
        break;
    case Controller::RightThumbX:
        output = m_axes.at(RightThumbX);
        break;
    case Controller::RightThumbY:
        output = m_axes.at(RightThumbY);
        break;
    }

    if (std::abs(output) <= deadzone)
        return 0;

    return output;
}
