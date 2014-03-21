#include <UtH/Platform/Android/InputTouch.hpp>

using namespace uth;

TouchInput::TouchUnit TouchInput::ID[8];

void TouchInput::Update(float deltaTime)
{

}

TouchInput::TouchUnit::TouchUnit()
{
	Motion = TouchMotion::NONE;
	m_curPos = umath::vector2();
}