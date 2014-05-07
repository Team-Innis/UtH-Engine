#include <UtH/Platform/Android/InputCommon.hpp>
#include <UtH/Platform/Android/InputTouch.hpp>
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
	TouchInput& Touch = uthInput.Touch;

	switch(Touch.Motion())
	{
	case TouchMotion::NONE:
		m_event = InputEvent::NONE;
		m_position = umath::vector2();
		break;
	case TouchMotion::STATIONARY:
		m_event = InputEvent::STATIONARY;
		m_position = Touch[0].GetPosition();
		break;
	case TouchMotion::TAP:
		m_event = InputEvent::TAP;
		m_position = Touch[0].GetPosition();
		break;
	case TouchMotion::DRAG:
		m_event = InputEvent::DRAG;
		m_position = Touch[0].GetPosition();
		break;
	case TouchMotion::PINCH_IN:
		m_event = InputEvent::ZOOM_OUT;
		m_position = Touch[0].GetPosition();
		break;
	case TouchMotion::PINCH_OUT:
		m_event = InputEvent::ZOOM_IN;
		m_position = Touch[0].GetPosition();
		break;
	case TouchMotion::MULTIPLE:
		switch(Touch[0].Motion())
		{
		case TouchMotion::STATIONARY:
			m_event = InputEvent::STATIONARY;
			break;
		case TouchMotion::PINCH_IN:
			m_event = InputEvent::ZOOM_OUT;
			break;
		case TouchMotion::PINCH_OUT:
			m_event = InputEvent::ZOOM_IN;
			break;
		default:
			WriteError("Probably undefined behaviour");
			break;
		}
		m_position = Touch[0].GetPosition();
		break;
	default:
		WriteError("Probably undefined behaviour");
		break;
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
