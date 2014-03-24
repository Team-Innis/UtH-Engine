#include <UtH/Platform/Android/InputTouch.hpp>

using namespace uth;

TouchInput::TouchUnit TouchInput::ID[10];

int TouchInput::DroidMessage(android_app* app, AInputEvent* droidInputEvent)
{
	if (AInputEvent_getType(droidInputEvent) == AINPUT_EVENT_TYPE_MOTION)
	{
		int32_t action = AMotionEvent_getAction(droidInputEvent);

		switch(action & AMOTION_EVENT_ACTION_MASK)
		{
		case AMOTION_EVENT_ACTION_DOWN:
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
			//When Screen is touched
			{
			int index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
				>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

			if(index >= m_maxInputs)
				break;

			ID[index].m_startPos.x = AMotionEvent_getX(droidInputEvent, index);
			ID[index].m_startPos.y = AMotionEvent_getY(droidInputEvent, index);
			ID[index].Motion = TouchMotion::STATIONARY;
			ID[index].m_startIndex = index;
			}
		case AMOTION_EVENT_ACTION_MOVE:
			//When pointer is moved
			{
			const int pointerCount = AMotionEvent_getPointerCount(droidInputEvent);

			for(int index = 0; index < pointerCount && index < m_maxInputs; index++)
			{
				ID[index].m_curPos.x = AMotionEvent_getX(droidInputEvent, index);
				ID[index].m_curPos.y = AMotionEvent_getY(droidInputEvent, index);
				ID[index].Motion = TouchMotion::DRAG;
			}
			}
			break;
		case AMOTION_EVENT_ACTION_UP:
		case AMOTION_EVENT_ACTION_CANCEL:
		case AMOTION_EVENT_ACTION_OUTSIDE:
			//If touch ends by taking finger away from screen or by some other event
			{
			int index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
				>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

			if(index >= m_maxInputs)
				break;

			ID[index].m_curPos.x = AMotionEvent_getX(droidInputEvent, index);
			ID[index].m_curPos.y = AMotionEvent_getY(droidInputEvent, index);

			for (unsigned int i = index; i < m_maxInputs-1; i++)
			{
				ID[i].m_startIndex = ID[i+1].m_startIndex;
				ID[i].m_startPos = ID[i+1].m_startPos;
				ID[i].m_downTime = ID[i+1].m_downTime;
				ID[i].Motion = ID[i+1].Motion;
			}
			}
			break;
		default:
			break;
		}
		return 1;
	}
	return 0;
}

void TouchInput::Update(float deltaTime)
{
	for(int i = 0 ; i < m_maxInputs; i++)
	{
		if(ID[i].Motion != TouchMotion::NONE)
			ID[i].m_downTime += deltaTime;
	}
}

const TouchInput::TouchUnit& TouchInput::operator[](unsigned int id) const
{
	if (id < m_maxInputs)
		return ID[id];
	WriteLog("TouchInput index out of range");
	return ID[m_maxInputs-1];
}