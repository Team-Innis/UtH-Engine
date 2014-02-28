#include "AndroidWindowImpl.hpp"
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Debug.hpp>


namespace uth
{

    void* AndroidWindowImpl::create(const WindowSettings& settings)
    {
		uth::AndroidEngine& androidengine = uth::AndroidEngine::getInstance();

        const EGLint attribs[] =
		{
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_NONE
		};

		EGLint attribList[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		EGLint format, numConfigs;

		androidengine.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		eglInitialize(androidengine.display,0,0);

		eglChooseConfig(androidengine.display, attribs, &androidengine.config, 1, &numConfigs);
		eglGetConfigAttrib(androidengine.display, androidengine.config, EGL_NATIVE_VISUAL_ID, &format);

		ANativeWindow_setBuffersGeometry(androidengine.app->window, 0, 0, format);

		androidengine.surface = eglCreateWindowSurface(androidengine.display, androidengine.surface, androidengine.app->window, NULL);
		androidengine.context = eglCreateContext(androidengine.display, androidengine.config, NULL, attribList);

		if(eglMakeCurrent(androidengine.display, androidengine.surface, androidengine.surface, androidengine.context) == false)
		{
			WriteLog("eglMakeCurrent failed");
			return (void*)NULL;
		}

		EGLint tempX;
		EGLint tempY;

		eglQuerySurface(androidengine.display, androidengine.surface, EGL_WIDTH, &tempX);
		eglQuerySurface(androidengine.display, androidengine.surface, EGL_HEIGHT, &tempY);

		androidengine.settings.size.x = tempX;
		androidengine.settings.size.y = tempY;

		glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glViewport(0,0,androidengine.settings.size.x,androidengine.settings.size.y);

		return (void*)NULL;
    }


    void* AndroidWindowImpl::destroy(void* handle)
    {
		uth::AndroidEngine& androidengine = uth::AndroidEngine::getInstance();

        if(androidengine.display != EGL_NO_DISPLAY)
		{
			eglMakeCurrent(androidengine.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			if(androidengine.display != EGL_NO_DISPLAY)
			{
				eglDestroyContext(androidengine.display, androidengine.context);
			}
			if (androidengine.surface != EGL_NO_SURFACE)
			{
				eglDestroySurface(androidengine.display, androidengine.surface);
			}
			eglTerminate(androidengine.display);
		}
		androidengine.display = EGL_NO_DISPLAY;
		androidengine.context = EGL_NO_CONTEXT;
		androidengine.surface = EGL_NO_SURFACE;
		
		return (void*)NULL;
    }


    void AndroidWindowImpl::clear(const bool clearDepth, const bool clearStencil, const float r, const float g, const float b, const float a)
    {
          oglCheck(glClear(GL_COLOR_BUFFER_BIT |
                         GL_DEPTH_BUFFER_BIT |
                         GL_STENCIL_BUFFER_BIT));
		oglCheck(glClearColor(r, g, b, a));

        if (!clearDepth) return;
			
        oglCheck(glClearDepthf(1.0f));
    }

    void AndroidWindowImpl::swapBuffers(void* handle)
    {
        //glxSwapBuffers();
    }
}