#include <UtH/Platform/Android/InputTouch.hpp>

using namespace uth;

TouchInput::TouchUnit TouchInput::ID[10];
unsigned int TouchInput::m_touchCount = 0;
TouchMotion TouchInput::m_motion = TouchMotion::NONE;
float TouchInput::m_curLength = 0.f;
float TouchInput::m_prevLength = 0.f;

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
			
			m_touchCount++;

			if(m_touchCount == 1)
			{
				m_motion = TouchMotion::STATIONARY;
			}
			else if(m_touchCount > 1)
			{
				m_motion = TouchMotion::MULTIPLE;
			}

			ID[index].m_startPos.x = AMotionEvent_getX(droidInputEvent, index);
			ID[index].m_startPos.y = AMotionEvent_getY(droidInputEvent, index);
			ID[index].m_motion = TouchMotion::STATIONARY;
			ID[index].m_startIndex = index;
			ID[index].m_downTime = 0.f;
			ID[index].m_tapped = false;
			}
			break;
		case AMOTION_EVENT_ACTION_MOVE:
			//When pointer is moved
			{
			const int pointerCount = AMotionEvent_getPointerCount(droidInputEvent);

			for(int index = 0; index < pointerCount && index < m_maxInputs; index++)
			{
				ID[index].m_curPos.x = AMotionEvent_getX(droidInputEvent, index);
				ID[index].m_curPos.y = AMotionEvent_getY(droidInputEvent, index);

				if((ID[index].m_curPos - ID[index].m_startPos).lengthSquared() >= 625.f)
				{
					ID[index].m_motion = TouchMotion::DRAG;
				}
			}
			}
			break;
		case AMOTION_EVENT_ACTION_UP:
		case AMOTION_EVENT_ACTION_POINTER_UP:
		case AMOTION_EVENT_ACTION_CANCEL:
		case AMOTION_EVENT_ACTION_OUTSIDE:
			//If touch ends by taking finger away from screen or by some other event
		{
			int index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
				>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

			if(index >= m_maxInputs)
				break;

			m_touchCount--;

			if(m_touchCount == 0)
			{
				m_motion = TouchMotion::NONE;
			}

			if(index <= 1)
			{
				m_prevLength = 0.f;
				m_curLength = 0.f;
			}

			if(action == AMOTION_EVENT_ACTION_UP || action == AMOTION_EVENT_ACTION_POINTER_UP)
			{
				if(ID[index].Motion() == TouchMotion::STATIONARY && ID[index].m_downTime <= 0.5f)
				{
					ID[index].m_tapped = true;
				}
			}

			ID[index].m_curPos.x = AMotionEvent_getX(droidInputEvent, index);
			ID[index].m_curPos.y = AMotionEvent_getY(droidInputEvent, index);

			if(!ID[index].m_tapped)
			{
				for (unsigned int i = index; i < m_maxInputs-1; i++)
				{
					ID[i].m_startIndex = ID[i+1].m_startIndex;
					ID[i].m_startPos = ID[i+1].m_startPos;
					ID[i].m_downTime = ID[i+1].m_downTime;
					ID[i].m_motion = ID[i+1].Motion();
				}
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
	for(int i = 0; i < m_maxInputs; i++)
	{
		if(!ID[i].m_tapped)
		{
			switch(ID[i].Motion())
			{
			case TouchMotion::STATIONARY:
				ID[i].m_downTime += deltaTime;
				break;
			case TouchMotion::TAP:
				for (unsigned int j = i; j < m_maxInputs-1; j++)
				{
					ID[j].m_startIndex = ID[j+1].m_startIndex;
					ID[j].m_startPos = ID[j+1].m_startPos;
					ID[j].m_downTime = ID[j+1].m_downTime;
					ID[j].m_motion = ID[j+1].Motion();
				}
				break;
			default:
				break;
			}
		}
		else
		{
			ID[i].m_tapped = false;
			ID[i].m_motion = TouchMotion::TAP;
			m_motion = TouchMotion::TAP;
		}
	}

	if(Motion() == TouchMotion::MULTIPLE || Motion() == TouchMotion::PINCH_IN || Motion() == TouchMotion::PINCH_OUT)
	{
		if((ID[0].Motion() == TouchMotion::DRAG && ID[1].Motion() == TouchMotion::DRAG) ||
			(ID[0].Motion() == TouchMotion::PINCH_IN && ID[1].Motion() == TouchMotion::PINCH_IN) ||
			(ID[0].Motion() == TouchMotion::PINCH_OUT && ID[1].Motion() == TouchMotion::PINCH_OUT))
		{
			m_prevLength = m_curLength;
			m_curLength = (ID[0].GetPosition()-ID[1].GetPosition()).length();

			if(m_curLength < m_prevLength)
			{
				m_motion = TouchMotion::PINCH_IN;
				ID[0].m_motion = TouchMotion::PINCH_IN;
				ID[1].m_motion = TouchMotion::PINCH_IN;
			}
			else if(m_curLength > m_prevLength && m_prevLength != 0.f)
			{
				m_motion = TouchMotion::PINCH_OUT;
				ID[0].m_motion = TouchMotion::PINCH_OUT;
				ID[1].m_motion = TouchMotion::PINCH_OUT;
			}
		}

		if(m_curLength == m_prevLength)
		{
			m_motion = TouchMotion::MULTIPLE;
			ID[0].m_motion = TouchMotion::STATIONARY;
			ID[1].m_motion = TouchMotion::STATIONARY;
		}
	}
}

const TouchInput::TouchUnit& TouchInput::operator[](unsigned int id) const
{
	if (id < m_maxInputs)
		return ID[id];
	WriteLog("TouchInput index out of range");
	return ID[m_maxInputs-1];
}

const int TouchInput::TouchUnit::GetStartIndex() const
{
	return m_startIndex;
}

const pmath::Vec2 TouchInput::TouchUnit::GetStartPosition() const
{
	return m_startPos;
}

const pmath::Vec2 TouchInput::TouchUnit::GetPosition() const
{
	return m_curPos;
}

const pmath::Vec2 TouchInput::TouchUnit::GetEndPosition() const
{
	return m_curPos;
}

const TouchMotion TouchInput::TouchUnit::Motion() const
{
	return m_motion;
}

const TouchMotion TouchInput::Motion() const
{
	return m_motion;
}