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
	uthInput.Touch
	m_event
}

bool CommonInput::operator == (InputEvent Event)
{

}
