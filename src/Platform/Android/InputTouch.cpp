#include <UtH/Platform/Android/InputTouch.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

TouchInput::TouchUnit TouchInput::ID;

umath::vector2 TouchInput::GetLastPos() const
{
	return ID.m_position;
}

void TouchInput::Update()
{
	if(ID.m_touched)
	{
		ID.m_touched = false;
	}
	else
	{
		ID.m_position = umath::vector2();
	}
}

TouchInput::TouchInput()
{

}

TouchInput::~TouchInput()
{

}