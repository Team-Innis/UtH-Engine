#include "Win32WindowImpl.hpp"
#include <UtH\Platform\OpenGL.hpp>
#include <UtH\Platform\OGLCheck.hpp>
#include <iostream>



namespace
{
    static unsigned int windowRefs = 0;
    static bool initialized = false;

    void manageWindowRefs()
    {
        if (windowRefs == 0)
        {
            glfwTerminate();
            initialized = false;
        }    
    }

    void ensureGLFWInit()
    {
        if (!initialized)
        {
            if (!glfwInit())
                std::exit(EXIT_FAILURE);

            initialized = true;
        }
    }
}


namespace uth
{

    void* Win32WindowImpl::create(const WindowSettings& settings)
    {
        ensureGLFWInit();

        GLFWwindow* wndwHandle;

        glfwWindowHint(GLFW_ALPHA_BITS, settings.useBlending ? 8 : 0);
        glfwWindowHint(GLFW_DEPTH_BITS, settings.useDepthBuffer ? 16 : 0);
        glfwWindowHint(GLFW_STENCIL_BITS, settings.useStencilBuffer ? 8 : 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

        int majorVer = settings.contextVersionMajor == 0 ? 4 : settings.contextVersionMajor,
            minorVer = settings.contextVersionMajor == 0 ? 4 : settings.contextVersionMinor;

        do
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);

            wndwHandle = glfwCreateWindow(settings.size.w, settings.size.h, settings.title.c_str(), settings.fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);

            if (--minorVer < 0)
            {
                --majorVer;
                minorVer = 9;
            }

        } while (!wndwHandle && majorVer > 0);


        if (!wndwHandle)
        {
            std::cout << "Failed to create an OpenGL context! Exiting..." <<std::endl;
            std::exit(EXIT_FAILURE);
        }

        ++windowRefs;
        glfwMakeContextCurrent(wndwHandle);

        glfwSetWindowPos(wndwHandle, settings.position.x, settings.position.y);
        glfwSwapInterval(settings.useVsync ? 1 : 0);

		std::cout << "glew init might produces GL_INVALID_ENUM error. Just ignore it" << std::endl;
		glewExperimental = GL_TRUE;
        oglCheck(glewInit());


        return static_cast<void*>(wndwHandle);
    }


    void* Win32WindowImpl::destroy(void* handle)
    {
        if (!handle) return handle;

        glfwDestroyWindow(static_cast<GLFWwindow*>(handle));

        handle = NULL;

        --windowRefs;
        manageWindowRefs();
        
        return handle;
    }


    void Win32WindowImpl::clear(const bool clearDepth, const bool clearStencil, const float r, const float g, const float b, const float a)
    {
        oglCheck(glClear(GL_COLOR_BUFFER_BIT |
                         GL_DEPTH_BUFFER_BIT |
                         GL_STENCIL_BUFFER_BIT));
		oglCheck(glClearColor(r, g, b, a));

        if (!clearDepth) return;
			
        oglCheck(glClearDepth(1));

        if (!clearStencil) return;

        oglCheck(glClearStencil(1));
    }

    void Win32WindowImpl::swapBuffers(void* handle)
    {
        if (!handle) return;

        glfwSwapBuffers(static_cast<GLFWwindow*>(handle));
    }
	
	void Win32WindowImpl::processMessages()
	{
		glfwPollEvents();
	}
}