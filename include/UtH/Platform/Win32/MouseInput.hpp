#pragma once
#ifndef MOUSEINPUT_H_UTH
#define MOUSEINPUT_H_UTH

#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Math/Vector2.hpp>
#include <vector>

namespace uth
{
	class MouseInput
	{
	public:
		MouseInput();
		~MouseInput();

		//bool IsButtonDown(Mouse::MButton Button);
		//umath::vector2 RelativeMousePosition();
		//umath::vector2 MousePosition();
		//int MouseWheel();


	private:
		umath::vector2 m_mousePos;
		umath::vector2 m_lastMousePos;
		std::vector<bool> m_buttonStates;
		std::vector<bool> m_lastbuttonStates;
		int m_mouseWheel;
		int m_lastMouseWheel;
	};
}

#endif