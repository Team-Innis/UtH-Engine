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

        void swapBuffers();

        void setViewport(const int x, const int y, const unsigned int width, const unsigned int height);

        const WindowSettings& getWindowSettings() const;

		// return true while window should remain open
		bool processMessages();

        umath::vector2 GetSize() const override;


        void* m_windowHandle;

    private:
        
        bool bind() override;

        WindowSettings m_windowSettings;

    };
}

#endif