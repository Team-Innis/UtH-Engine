#include <UtH/Platform/Common/InputCommon.hpp>
#include <UtH/Platform/Input.hpp>

using namespace uth;

const InputEvent& CommonInput::Event() const
{
	return m_event;
}
const umath::vector2 CommonInput::Position() const
{
	return m_position;
}
		
void CommonInput::Update()
{
	MouseInput& Mouse = uthInput.Mouse;
	const float wheel = Mouse.Wheel().y;
	if (wheel != 0)
	{
		if (wheel > 0)
			m_event = InputEvent::ZOOM_IN;
		else
			m_event = InputEvent::ZOOM_OUT;

		m_position = Mouse.Position();
	}
	else if(Mouse.IsButtonDown(uth::Mouse::MButton::MS1) ||
		Mouse.IsButtonDown(uth::Mouse::MButton::MS2) ||
		Mouse.IsButtonDown(uth::Mouse::MButton::MS3))
	{
		if (Mouse.Movement() == umath::vector2())
		{
			if (m_event == InputEvent::NONE || m_event == InputEvent::STATIONARY)
				m_event = InputEvent::STATIONARY;
			else
				m_event = InputEvent::DRAG;
		}
		else
		{
			m_event = InputEvent::DRAG;
		}
		m_position = Mouse.Position();
	}
	else if(Mouse.IsButtonReleased(uth::Mouse::MButton::MS1) ||
		Mouse.IsButtonReleased(uth::Mouse::MButton::MS2) ||
		Mouse.IsButtonReleased(uth::Mouse::MButton::MS3))
	{
		m_event = InputEvent::CLICK;
		m_position = Mouse.Position();
	}
	else
	{
		m_event = InputEvent::NONE;
		m_position = umath::vector2();
	}
}

bool CommonInput::operator == (const InputEvent& Event) const
{
	return m_event == Event;
}

bool CommonInput::operator != (const InputEvent& Event) const
{
	return m_event != Event;
}