#pragma once
#ifndef INPUT_H_UTH
#define INPUT_H_UTH

#include <UtH/Platform/Singleton.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/Configuration.hpp>
#include <UtH/Platform/Debug.hpp>

#if defined(UTH_SYSTEM_ANDROID)
	#include <UtH/Platform/Android/InputCommon.hpp>
	#include <UtH/Platform/Android/InputKeyboard.hpp>
	#include <UtH/Platform/Android/InputMouse.hpp>
	#include <UtH/Platform/Android/InputTouch.hpp>
    #include <UtH/Platform/Android/InputSensor.hpp>
    #include <UtH/Platform/Android/InputController.hpp>

#elif defined(UTH_SYSTEM_WINDOWS) || defined(UTH_SYSTEM_LINUX)
    #include <UtH/Platform/Common/InputCommon.hpp>
    #include <UtH/Platform/Common/InputKeyboard.hpp>
    #include <UtH/Platform/Common/InputMouse.hpp>
    #include <UtH/Platform/Common/InputTouch.hpp>
    #include <UtH/Platform/Common/InputSensor.hpp>
    #include <UtH/Platform/Common/InputController.hpp>


#else
	#error No input for such platform
#endif

#include <functional>

#define uthInput uth::Input::getInstance()

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
        SensorInput Sensor;
		KeyboardInput Keyboard;
        ControllerInput Controller;
		CommonInput Common;

		void SetAndroidBackFunction(std::function<void()> function);

		// This shouldn't be used outside main.cpp
		bool RunBackButton();

		void Update(float deltaTime);
		void SetWindow(void *windowHandle);
	private:
		void *m_windowHandle;
		friend class UtHEngine;

		std::function<void()> f_androidBackButton;
        bool m_handleBackButton;
	};
}

#endif