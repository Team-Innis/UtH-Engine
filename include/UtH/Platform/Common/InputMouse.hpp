#pragma once
#ifndef INPUTMOUSE_H_UTH
#define INPUTMOUSE_H_UTH

#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Platform/Window.hpp>

#include <UtH/Math/Vector2.hpp>

#include <vector>

namespace uth
{
	
	namespace Mouse
	{
		enum MButton
		{
			MS1		= 0,
			LEFT	= MS1,
			MS2		= 1,
			RIGHT	= MS2,
			MS3		= 2,
			MIDDLE	= MS3,
			MS4		= 3,
			X1		= MS4,
			MS5		= 4,
			X2		= MS5,
			COUNT
		};
	}

	class MouseInput : public InputBase
	{
	public:
		MouseInput();
		~MouseInput();

		void Initiate();
		void Update();

		bool IsButtonDown(Mouse::MButton Button);
		bool IsButtonPressed(Mouse::MButton Button);
		bool IsButtonReleased(Mouse::MButton Button);

		umath::vector2 MousePosition();
		umath::vector2 MouseMovement();
		umath::vector2 MouseWheel();

	private:

		umath::vector2 m_pos;
		umath::vector2 m_Lpos;
		std::vector<bool> m_buttons;
		std::vector<bool> m_Lbuttons;
		umath::vector2 m_scroll;
	};
}

#endif