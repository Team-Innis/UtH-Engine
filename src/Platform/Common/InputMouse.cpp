#include <UtH/Platform/Common/InputMouse.hpp>
#include <UtH/Platform/Debug.hpp>
#include <GLFW/glfw3.h>

namespace uth
{
	static double MOUSE_WHEEL_X = 0;
	static double MOUSE_WHEEL_Y = 0;
	
	void scroll(GLFWwindow*, double x, double y)
	{
		MOUSE_WHEEL_X += x;
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
		m_pos.x = static_cast<float>(x);
		m_pos.y = static_cast<float>(y);

		//WriteLog("\n%f	%f	", x,y);

		for (int i = 0; i < Mouse::COUNT; i++)
		{
			m_Lbuttons.at(i) = m_buttons.at(i);
			m_buttons.at(i) = glfwGetMouseButton(window, i) == 1;
			//WriteLog(" %d", glfwGetMouseButton(window, i));
		}
		const float scrollX = static_cast<float>(MOUSE_WHEEL_X);
		MOUSE_WHEEL_X = 0;

		const float scrollY = static_cast<float>(MOUSE_WHEEL_Y);
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
	pmath::Vec2 MouseInput::Position()
	{
		return m_pos;
	}
	pmath::Vec2 MouseInput::Movement()
	{
		return m_pos - m_Lpos;
	}

	pmath::Vec2 MouseInput::Wheel()
	{
		return m_scroll;
	}
}

