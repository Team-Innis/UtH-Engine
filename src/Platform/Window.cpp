#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Graphics.hpp>


#if defined(UTH_SYSTEM_WINDOWS) || defined(UTH_SYSTEM_LINUX) || defined(UTH_SYSTEM_MACOS)

#include <UtH/Platform/Common/CommonWindowImpl.hpp>
typedef uth::CommonWindowImpl WindowImpl;

#elif defined(UTH_SYSTEM_ANDROID)

#include <UtH/Platform/Android/AndroidWindowImpl.hpp>
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
		: m_windowHandle(nullptr)
	{
        // This is patchy. Multiple windows aren't supported.
        WindowImpl::setResizeCallback([this](int x, int y)
        {
            SetViewport(pmath::Recti(0, 0, x, y));
            m_windowSettings.size = pmath::Vec2i(x, y);
        });
		create(settings);
		m_windowSettings = settings;
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

	bool Window::processMessages()
	{
		return WindowImpl::processMessages(m_windowHandle);
	}
	void Window::swapBuffers()
	{
		WindowImpl::swapBuffers(m_windowHandle);
	}

	const WindowSettings& Window::getWindowSettings() const
	{
		return m_windowSettings;
	}
	pmath::Vec2 Window::GetSize() const
	{
		return m_windowSettings.size;
	}

	bool Window::bind()
	{
		uth::Graphics::BindFrameBuffer(0);

		const pmath::Rect& vp = GetViewport();
		uth::Graphics::SetViewport(
			static_cast<int>(vp.position.x + 0.5f),
			static_cast<int>(vp.position.y + 0.5f),
			static_cast<int>(vp.size.x + 0.5f),
			static_cast<int>(vp.size.y + 0.5f)
			);

		return true;
	}
}