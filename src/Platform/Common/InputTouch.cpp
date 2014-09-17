#include <UtH/Platform/Common/InputTouch.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

const TouchInput::TouchUnit& TouchInput::operator[](unsigned int id) const
{
	WriteLog("Touch not defined on computer.");
	return ID[id];
}

const TouchMotion TouchInput::Motion() const
{
	WriteLog("Touch not defined on computer.");
	return ID[0].Motion();
}

void TouchInput::Update(float)
{

}


const TouchMotion TouchInput::TouchUnit::Motion() const
{
	WriteLog("Touch not defined on computer.");
	return m_motion;
}

const int TouchInput::TouchUnit::GetStartIndex() const
{
	WriteLog("Touch not defined on computer.");
	return 0;
}

const pmath::Vec2 TouchInput::TouchUnit::GetStartPosition() const
{
	WriteLog("Touch not defined on computer.");
	return pmath::Vec2();
}

const pmath::Vec2 TouchInput::TouchUnit::GetPosition() const
{
	WriteLog("Touch not defined on computer.");
	return pmath::Vec2();
}

const pmath::Vec2 TouchInput::TouchUnit::GetEndPosition() const
{
	WriteLog("Touch not defined on computer.");
	return pmath::Vec2();
}
