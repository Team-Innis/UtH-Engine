#include <UtH/Platform/Common/CommonWindowImpl.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Graphics.hpp>
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

    void* CommonWindowImpl::create(const WindowSettings& settings)
    {
        ensureGLFWInit();

        GLFWwindow* wndwHandle;

        glfwWindowHint(GLFW_ALPHA_BITS, settings.useBlending ? 8 : 0);
        glfwWindowHint(GLFW_DEPTH_BITS, settings.useDepthBuffer ? 16 : 0);
        glfwWindowHint(GLFW_STENCIL_BITS, settings.useStencilBuffer ? 8 : 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
        glfwWindowHint(GLFW_SAMPLES, settings.antialiasingSamples);

        int majorVer = settings.contextVersionMajor == 0 ? 4 : settings.contextVersionMajor,
            minorVer = settings.contextVersionMajor == 0 ? 4 : settings.contextVersionMinor;

        do
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVer);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVer);

            wndwHandle = glfwCreateWindow((int)settings.size.x, (int)settings.size.y, settings.title.c_str(), settings.fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);

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

        glfwSetWindowPos(wndwHandle, (int)settings.position.x, (int)settings.position.y);
        glfwSwapInterval(settings.useVsync ? 1 : 0);

		//std::cout << "glew init might produce GL_INVALID_ENUM error. Just ignore it" << std::endl;
		glewExperimental = GL_TRUE;

        /////////////////////////////
        CheckGLError("before glewInit");
        glewInit();
        GLenum errCode = glGetError();
        if (errCode != GL_INVALID_ENUM && errCode != GL_NO_ERROR)
        {
            WriteError("Window creation failed!!! D:");
            assert(false);
        }

        //oglCheck(glewInit());
        ////////////////////////////

		if(majorVer >= 3)
        {
            GLuint vertexArray;
            glGenVertexArrays(1, &vertexArray);
            glBindVertexArray(vertexArray);
        }


        return static_cast<void*>(wndwHandle);
    }


    void* CommonWindowImpl::destroy(void* handle)
    {
        if (!handle) return handle;

        glfwDestroyWindow(static_cast<GLFWwindow*>(handle));

        handle = NULL;

        --windowRefs;
        manageWindowRefs();

        return handle;
    }


    void CommonWindowImpl::clear(const float r, const float g, const float b, const float a)
    {
        uth::Graphics::Clear(r, g, b, a);
    }

    void CommonWindowImpl::swapBuffers(void* handle)
    {
        if (!handle) return;

        glfwSwapBuffers(static_cast<GLFWwindow*>(handle));
    }

	bool CommonWindowImpl::processMessages(void* handle)
	{
		if (!handle) return false;

		glfwPollEvents();

		return glfwWindowShouldClose(static_cast<GLFWwindow*>(handle)) != 0;
	}
}