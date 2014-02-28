#include <UtH/Platform/Win32/MouseInput.hpp>
#include <GLFW/glfw3.h>

namespace uth
{
	MouseInput::MouseInput()
		: m_buttonStates(Mouse::MButton::COUNT, false)
	{}
	MouseInput::~MouseInput()
	{}
	//bool MouseInput::IsButtonDown(Mouse::MButton Button)
	//{}
	//umath::vector2 MouseInput::RelativeMousePosition()
	//{}
	//umath::vector2 MouseInput::MousePosition()
	//{}
	//int MouseInput::MouseWheel()
	//{}
}