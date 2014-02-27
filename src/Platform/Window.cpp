#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>


#if defined(UTH_SYSTEM_WINDOWS)

#include <Platform/Win32/Win32WindowImpl.hpp>
typedef uth::Win32WindowImpl WindowImpl;

#elif defined(UTH_SYSTEM_ANDROID)

#include <../src/Platform/Android/AndroidWindowImpl.hpp>
typedef uth::AndroidWindowImpl WindowImpl;

#endif



namespace uth
{
    Window::Window()
        : m_windowHandle(NULL),
          m_windowSettings()
    {

    }

    Window::Window(const WindowSettings& settings)
        : m_windowHandle(NULL),
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

        return m_windowHandle;
    }


    void Window::destroy()
    {
        WindowImpl::destroy(m_windowHandle);
        m_windowHandle = NULL;
    }


    void Window::clear(const float r, const float g, const float b, const float a)
    {
        WindowImpl::clear(m_windowSettings.useDepthBuffer,
                          m_windowSettings.useStencilBuffer,
                          r, g, b, a);
    }

    void Window::swapBuffers()
    {
        WindowImpl::swapBuffers(m_windowHandle);
    }

    void Window::setViewport(const int x, const int y, const unsigned int width, const unsigned int height)
    {
        oglCheck(glViewport(x, y, width, height));
    }

    const WindowSettings& Window::getWindowSettings() const
    {
        return m_windowSettings;
    }
	
	bool Window::processMessages()
	{
		return WindowImpl::processMessages(m_windowHandle);
	}
}