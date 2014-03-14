#include <UtH/Platform/Android/InputTouch.hpp>

using namespace uth;

TouchInput::TouchUnit TouchInput::ID;

umath::vector2 TouchInput::GetLastPos() const
{
	return ID.m_position;
}

void TouchInput::Update()
{

}

TouchInput::TouchInput()
{

}

TouchInput::~TouchInput()
{

}