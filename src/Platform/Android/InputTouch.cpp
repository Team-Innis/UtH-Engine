#include <UtH/Platform/Android/InputTouch.hpp>

using namespace uth;

TouchInput::TouchUnit TouchInput::ID;

umath::vector2 TouchInput::GetLastPos() const
{
	return ID.m_position;
}

void TouchInput::Update(float deltaTime)
{
	if(ID.m_touched)
	{
		m_touchTime += deltaTime;

		if(m_touchTime >= 0.5f)
		{
			
		}
	}
	else
	{
		m_touchTime = 0.0f;
		motion = TouchMotion::NONE;
	}
}

TouchInput::TouchInput()
{
	motion = TouchMotion::NONE;
	m_touchTime = 0;
}

TouchInput::~TouchInput()
{

}