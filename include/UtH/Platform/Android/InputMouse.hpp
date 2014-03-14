#pragma once
#ifndef MOUSEINPUT_H_UTH
#define MOUSEINPUT_H_UTH

#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/Common/InputBase.hpp>

#include <UtH/Math/Vector2.hpp>

#include <vector>

#include <UtH\Platform\Debug.hpp>

namespace uth
{
	//extern class Input;
	class MouseInput : public InputBase
	{
	public:
		MouseInput(){}
		~MouseInput(){}

		bool IsButtonDown(Mouse::MButton Button){return false;}
		bool IsButtonPressed(Mouse::MButton Button){return false;}
		bool IsButtonReleased(Mouse::MButton Button){return false;}

		umath::vector2 MousePosition()
		{
			WriteLog("No Mouse with android. Returning zero");
			return umath::vector2();
		}
		umath::vector2 MouseMovement(){}
		//int MouseWheel();


		void Update(){}
	private:

		//friend class Input;
	};
}

#endif