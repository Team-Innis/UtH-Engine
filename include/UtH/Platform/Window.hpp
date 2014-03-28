#pragma once
#ifndef WINDOW_H_UTH
#define WINDOW_H_UTH

#include <UtH/Platform/WindowSettings.hpp>
#include <UtH/Renderer/RenderTarget.hpp>

#define uthWindow uth::Window::getInstance()

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

        void clear(const float r, const float g, const float b, const float a = 1.f);

        void swapBuffers();

        void setViewport(const int x, const int y, const unsigned int width, const unsigned int height);

        const WindowSettings& getWindowSettings() const;

		// return true while window should remain open
		bool processMessages();

        umath::vector2 GetSize() const;

        bool Bind();


        void* m_windowHandle;

    private:

        WindowSettings m_windowSettings;

    };
}

#endif