#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Graphics.hpp>


#if defined(UTH_SYSTEM_WINDOWS)

#include <UtH/Platform/Win32/Win32WindowImpl.hpp>
typedef uth::Win32WindowImpl WindowImpl;

#elif defined(UTH_SYSTEM_LINUX)

#include <UtH/Platform/Linux/LinuxWindowImpl.hpp>
typedef uth::LinuxWindowImpl WindowImpl;

#elif defined(UTH_SYSTEM_ANDROID)

#include <../src/Platform/Android/AndroidWindowImpl.hpp>
typedef uth::AndroidWindowImpl WindowImpl;

#endif



namespace uth
{
    Window::Window()
        : m_windowHandle(nullptr),
          m_windowSettings()
    {

    }

    Window::Window(const WindowSettings& settings)
        : m_windowHandle(nullptr),
          m_windowSettings(settings)
    {
        create(m_windowSettings);
    }

    Window::~Window()
    {
        destroy();
    }


    bool Window::create(const WindowSettings& settings)
    {
        destroy();

        m_windowHandle = WindowImpl::create(settings);

		return m_windowHandle != nullptr;
    }


    void Window::destroy()
    {
        WindowImpl::destroy(m_windowHandle);
        m_windowHandle = nullptr;
    }


    void Window::swapBuffers()
    {
        WindowImpl::swapBuffers(m_windowHandle);
    }

    const WindowSettings& Window::getWindowSettings() const
    {
        return m_windowSettings;
    }
	
	bool Window::processMessages()
	{
		return WindowImpl::processMessages(m_windowHandle);
	}

    umath::vector2 Window::GetSize() const
    {
        return m_windowSettings.size;
    }

    bool Window::bind()
    {
        uth::Graphics::BindFrameBuffer(0);
        return true;
    }
}