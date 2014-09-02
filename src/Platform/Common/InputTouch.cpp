#include <UtH/Platform/Common/InputTouch.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

const TouchInput::TouchUnit& TouchInput::operator[](unsigned int id) const
{
	WriteLog("Touch not defined on computer.");
	return ID[id];
}

const TouchMotion::TouchMotion TouchInput::Motion() const
{
	WriteLog("Touch not defined on computer.");
	return ID[0].Motion();
}

void TouchInput::Update(float dt)
{

}


const TouchMotion::TouchMotion TouchInput::TouchUnit::Motion() const
{
	WriteLog("Touch not defined on computer.");
	return m_motion;
}

const int TouchInput::TouchUnit::GetStartIndex() const
{
	WriteLog("Touch not defined on computer.");
	return 0;
}

const umath::vector2 TouchInput::TouchUnit::GetStartPosition() const
{
	WriteLog("Touch not defined on computer.");
	return umath::vector2();
}

const umath::vector2 TouchInput::TouchUnit::GetPosition() const
{
	WriteLog("Touch not defined on computer.");
	return umath::vector2();
}

const umath::vector2 TouchInput::TouchUnit::GetEndPosition() const
{
	WriteLog("Touch not defined on computer.");
	return umath::vector2();
}
