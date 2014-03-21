#pragma once
#ifndef TOUCHINPUT_H_UTH
#define TOUCHINPUT_H_UTH

#include <UtH/Math/Vector2.hpp>
#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Platform/Debug.hpp>

#include <android/input.h>

namespace uth
{
	enum class TouchMotion
	{
		NONE = 0,
		TAP,
		DRAG,
		PINCH_IN,
		PINCH_OUT
	};

	class TouchInput
	{
	private:
		class TouchUnit
		{
		private:
			umath::vector2 m_startPos;
			umath::vector2 m_curPos;
			umath::vector2 m_endPos;
		public:
			TouchMotion Motion;
			umath::vector2 GetPosition() const;
			TouchUnit();
		};	
	public:
		static TouchUnit ID[8];
		static int DroidMessage(struct android_app* app, AInputEvent* droidInputEvent)
		{
			if (AInputEvent_getType(droidInputEvent) == AINPUT_EVENT_TYPE_MOTION)
			{
				if(AMotionEvent_getAction(droidInputEvent) == AMOTION_EVENT_ACTION_DOWN)
				{
					//When Screen is touched
					//m_startPos =GetPosition
				}
				else if(AMotionEvent_getAction(droidInputEvent) == AMOTION_EVENT_ACTION_MOVE)
				{
					//When Touch position changes
				}
				else if(AMotionEvent_getAction(droidInputEvent) == AMOTION_EVENT_ACTION_UP ||
					AMotionEvent_getAction(droidInputEvent) == AMOTION_EVENT_ACTION_CANCEL ||
					AMotionEvent_getAction(droidInputEvent) == AMOTION_EVENT_ACTION_OUTSIDE)
				{
					//If touch ends by taking finger away from screen or by some other event
					//m_endPos = m_curPos;
					//m_curPos = umath::vector2();
				}
				return 1;
			}
			return 0;
		}
	
		void Update(float deltaTime);
	};
}

#endif