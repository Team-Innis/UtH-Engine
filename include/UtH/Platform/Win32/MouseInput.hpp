#pragma once
#ifndef MOUSEINPUT_H_UTH
#define MOUSEINPUT_H_UTH

#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Platform/Window.hpp>

#include <UtH/Math/Vector2.hpp>

#include <vector>

namespace uth
{
	//extern class Input;
	class MouseInput
	{
	public:
		MouseInput();
		~MouseInput();

		bool IsButtonDown(Mouse::MButton Button);
		bool IsButtonPressed(Mouse::MButton Button);
		bool IsButtonReleased(Mouse::MButton Button);

		umath::vector2 MousePosition();
		umath::vector2 MouseMovement();
		//int MouseWheel();


		void Update(void* windowHandle);
	private:

		umath::vector2 m_pos;
		umath::vector2 m_Lpos;
		std::vector<bool> m_buttons;
		std::vector<bool> m_Lbuttons;
		umath::vector2 m_scroll;
		umath::vector2 m_Lscroll;

		//friend class Input;
	};
}

#endif