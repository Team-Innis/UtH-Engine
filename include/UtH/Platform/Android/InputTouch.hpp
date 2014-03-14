#pragma once
#ifndef TOUCHINPUT_H_UTH
#define TOUCHINPUT_H_UTH

#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Math/Vector2.hpp>
#include <UtH/Platform/Common/InputBase.hpp>

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
	public:
		static TouchUnit ID;

		/// Do not use this in scenes
		static int ProcessMessages(struct android_app* app, AInputEvent* eventMSG)
		{
			if (AInputEvent_getType(eventMSG) == AINPUT_EVENT_TYPE_MOTION)
			{
				//if(event == down)
				ID.m_position.x = AMotionEvent_getX(eventMSG, 0);
				ID.m_position.y = AMotionEvent_getY(eventMSG, 0);
				ID.m_touched = true;
				//if(event == up)
				//reset position & touched = false
				return 1;
			}
			return 0;
		}
		umath::vector2 GetLastPos() const;

		void Update();

		TouchInput();
		~TouchInput();
	};
}

#endif