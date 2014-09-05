#pragma once
#ifndef TOUCHINPUT_H_UTH
#define TOUCHINPUT_H_UTH

#include <pmath/Vector2.hpp>
#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Platform/Debug.hpp>

#include <android/input.h>

struct android_app;

namespace uth
{
	enum class TouchMotion
	{
		NONE = 0,
		STATIONARY,
		TAP,
		DRAG,
		PINCH_IN,
		PINCH_OUT,
		MULTIPLE
	};

	class TouchInput : public InputBase
	{
	private:
		class TouchUnit
		{
			friend class TouchInput;
		private:
			int m_startIndex;
			pmath::Vec2 m_startPos;
			pmath::Vec2 m_curPos;
			float m_downTime;
			TouchMotion m_motion;
			bool m_tapped;
		public:
			const TouchMotion Motion() const;
			const int GetStartIndex() const;
			const pmath::Vec2 GetStartPosition() const;
			const pmath::Vec2 GetPosition() const;
			const pmath::Vec2 GetEndPosition() const;
		};	
		static const int m_maxInputs = 10;
		static TouchMotion m_motion;
		static TouchUnit ID[m_maxInputs];
		static unsigned int m_touchCount;

		static float m_curLength;
		static float m_prevLength;
	public:
		const TouchMotion Motion() const;
		static int DroidMessage(android_app* app, AInputEvent* droidInputEvent);

		void Update(float deltaTime);

		const TouchUnit& operator[](unsigned int id) const;
	};
}

#endif