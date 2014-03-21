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
	class TouchInput : public InputBase
	{
	private:
		class TouchUnit
		{
			friend class TouchInput;
			bool m_touched;
			umath::vector2 m_position;

			TouchUnit()
			{
				m_touched = false;
				m_position = umath::vector2();
			}
		};

		float m_touchTime;
	public:
		enum class TouchMotion
		{
			NONE = 0,
			PINCH_IN,
			PINCH_OUT,
			TAP,
			DRAG
		};

		TouchMotion motion;

		static TouchUnit ID;

		/// Do not use this in scenes
		static int ProcessMessages(struct android_app* app, AInputEvent* eventMSG)
		{
			if (AInputEvent_getType(eventMSG) == AINPUT_EVENT_TYPE_MOTION)
			{
				if(AMotionEvent_getAction(eventMSG) == AMOTION_EVENT_ACTION_DOWN)
				{
					ID.m_position.x = AMotionEvent_getX(eventMSG, 0);
					ID.m_position.y = AMotionEvent_getY(eventMSG, 0);
					ID.m_touched = true;
					WriteLog("Touch");
				}
				else if(AMotionEvent_getAction(eventMSG) == AMOTION_EVENT_ACTION_MOVE)
				{
					ID.m_position.x = AMotionEvent_getX(eventMSG, 0);
					ID.m_position.y = AMotionEvent_getY(eventMSG, 0);
					ID.m_touched = true;
				}
				else if(AMotionEvent_getAction(eventMSG) == AMOTION_EVENT_ACTION_UP ||
					AMotionEvent_getAction(eventMSG) == AMOTION_EVENT_ACTION_CANCEL ||
					AMotionEvent_getAction(eventMSG) == AMOTION_EVENT_ACTION_OUTSIDE)
				{
					ID.m_position.x = -1;
					ID.m_position.y = -1;
					ID.m_touched = false;
				}
				return 1;
			}
			return 0;
		}
		umath::vector2 GetLastPos() const;

		void Update(float deltaTime);

		TouchInput();
		~TouchInput();
	};
}

#endif