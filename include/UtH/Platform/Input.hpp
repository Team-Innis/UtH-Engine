#pragma once
#ifndef INPUT_H_UTH
#define INPUT_H_UTH

#include <UtH/Platform/Singleton.hpp>
#include <UtH/Platform/Window.hpp>

#include <UtH/Engine/UtHEngine.h>

#include <UtH/Platform/Win32/MouseInput.hpp>



#if defined(UTH_SYSTEM_ANDROID)
	//#include <UtH/Platform/Android/InputCommon.hpp>
	//#include <UtH/Platform/Android/InputKeyboard.hpp>
	//#include <UtH/Platform/Android/InputMouse.hpp>
	//#include <UtH/Platform/Android/InputTouch.hpp>
#elif defined(UTH_SYSTEM_WINDOWS)
	#include <UtH/Platform/Win32/CommonInput.hpp>
	#include <UtH/Platform/Win32/KeyboardInput.hpp>
	#include <UtH/Platform/Win32/MouseInput.hpp>
	#include <UtH/Platform/Win32/TouchInput.hpp>
#else
	#error No input for such platform
#endif

#define UTHInput uth::Input::getInstance()

namespace uth
{
	class Input : public Singleton<Input>
	{
		Input();
		~Input();
		friend class Singleton<Input>;
	public:
		MouseInput Mouse;
		TouchInput Touch;
		KeyboardInput Keyboard;
		CommonInput Common;

		void Update();
		void SetWindow(void *windowHandle);
	private:
		void *m_windowHandle;
		friend class UtHEngine;
	};
}

#endif