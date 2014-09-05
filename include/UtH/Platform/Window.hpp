#pragma once
#ifndef WINDOW_H_UTH
#define WINDOW_H_UTH

#include <UtH/Platform/WindowSettings.hpp>
#include <UtH/Renderer/RenderTarget.hpp>

namespace uth
{

	class Window : public RenderTarget
	{
	public:
		Window();
		Window(const WindowSettings& settings);
		~Window();

		bool create(const WindowSettings& settings);
		void destroy();

		// return true while window should remain open
		bool processMessages();
		void swapBuffers();

		const WindowSettings& getWindowSettings() const;
		pmath::Vec2 GetSize() const;

		void* m_windowHandle;

	private:

		bool bind();

		WindowSettings m_windowSettings;

	};
}

#endif