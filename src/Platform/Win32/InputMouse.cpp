#include <UtH/Platform/Win32/InputMouse.hpp>
#include <UtH/Platform/Debug.hpp>
#include <GLFW/glfw3.h>

namespace uth
{
	static double MOUSE_WHEEL_X = 0;
	static double MOUSE_WHEEL_Y = 0;
	
	void scroll(GLFWwindow *window, double x, double y)
	{
		MOUSE_WHEEL_Y += y;
	}

	MouseInput::MouseInput()
		: m_buttons(Mouse::COUNT, false),
		  m_Lbuttons(m_buttons)
	{}
	MouseInput::~MouseInput()
	{}

	void MouseInput::Initiate()
	{
		GLFWwindow *window = static_cast<GLFWwindow*>(windowHandle);
		glfwSetScrollCallback(window,scroll);
	}
	void MouseInput::Update()
	{
		GLFWwindow *window = static_cast<GLFWwindow*>(windowHandle);

		m_Lpos = m_pos;
		double x,y;
		glfwGetCursorPos(window,&x,&y);
		m_pos.x = x;
		m_pos.y = y;

		//WriteLog("\n%f	%f	", x,y);

		for (int i = 0; i < Mouse::COUNT; i++)
		{
			m_Lbuttons.at(i) = m_buttons.at(i);
			m_buttons.at(i) = (bool)glfwGetMouseButton(window, i);
			//WriteLog(" %d", glfwGetMouseButton(window, i));
		}
		const float scrollX = MOUSE_WHEEL_X;
		MOUSE_WHEEL_X = 0;

		const float scrollY = MOUSE_WHEEL_Y;
		MOUSE_WHEEL_Y = 0;

		m_scroll.x = scrollX;
		m_scroll.y = scrollY;
		
		//WriteLog("	%f , %f", m_scroll.x,m_scroll.y);
	}

	bool MouseInput::IsButtonDown(Mouse::MButton Button)
	{
		return m_buttons.at(Button);
	}
	bool MouseInput::IsButtonPressed(Mouse::MButton Button)
	{
		return m_buttons.at(Button) && !m_Lbuttons.at(Button);
	}
	bool MouseInput::IsButtonReleased(Mouse::MButton Button)
	{
		return !m_buttons.at(Button) && m_Lbuttons.at(Button);
	}
	umath::vector2 MouseInput::MousePosition()
	{
		return m_pos;
	}
	umath::vector2 MouseInput::MouseMovement()
	{
		return m_pos - m_Lpos;
	}

	umath::vector2 MouseInput::MouseWheel()
	{
		return m_scroll;
	}
}

