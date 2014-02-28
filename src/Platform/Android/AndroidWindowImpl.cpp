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
			EGL_BLUE_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_RED_SIZE, 8,
			EGL_ALPHA_SIZE, 8,
			EGL_DEPTH_SIZE, 8,
			EGL_STENCIL_SIZE, 8,
			EGL_NONE
		};

		EGLint attribList[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, 2,
			EGL_NONE
		};

		EGLint format, numConfigs;

		androidengine.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		WriteLog("eglGetDisplay %d", (int)androidengine.display);
		CheckEGLError();

		if(androidengine.display == EGL_NO_DISPLAY)
		{
			WriteLog("display nodisplay");
		}


		eglInitialize(androidengine.display,0,0);
			WriteLog("eglInitialize succeeded");
		CheckEGLError();
		
		//eglChooseConfig(androidengine.display, attribs, NULL, 1, &numConfigs);
		//WriteLog("Configs: %d", (int)numConfigs);
		
		eglChooseConfig(androidengine.display, attribs, &androidengine.config, 1, &numConfigs);
		CheckEGLError();
			WriteLog("eglChooseConfig succeeded");
		eglGetConfigAttrib(androidengine.display, androidengine.config, EGL_NATIVE_VISUAL_ID, &format);
		CheckEGLError();
			WriteLog("eglGetConfigAttrib succeeded");

		

		//ANativeWindow_setBuffersGeometry(androidengine.app->window, 0, 0, 0);
		//CheckEGLError();
		//	WriteLog("ANativeWindow_setBuffersGeometry succeeded");

		androidengine.surface = eglCreateWindowSurface(androidengine.display, androidengine.config, androidengine.app->window, NULL);
		CheckEGLError();
			WriteLog("eglCreateWindowSurface succeeded");
		androidengine.context = eglCreateContext(androidengine.display, androidengine.config, EGL_NO_CONTEXT, attribList);
		CheckEGLError();
			WriteLog("eglCreateContext succeeded");

		if(eglMakeCurrent(androidengine.display, androidengine.surface, androidengine.surface, androidengine.context) == EGL_FALSE)
		{
			CheckEGLError();
			WriteLog("eglMakeCurrent failed");
			return (void*)NULL;
		}

		EGLint tempX;
		EGLint tempY;

		eglQuerySurface(androidengine.display, androidengine.surface, EGL_WIDTH, &tempX);
		CheckEGLError();
		eglQuerySurface(androidengine.display, androidengine.surface, EGL_HEIGHT, &tempY);
		CheckEGLError();

		androidengine.settings.size.x = tempX;
		androidengine.settings.size.y = tempY;

		//glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
		//glEnable(GL_CULL_FACE);
		//glEnable(GL_DEPTH_TEST);

		WriteLog("+++++++++++++++++++++++++++++++++++++++");
		WriteLog((const char*)glGetString(GL_VERSION));
		WriteLog("+++++++++++++++++++++++++++++++++++++++");

		return nullptr;
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
		eglSwapBuffers(uth::AndroidEngine::getInstance().display, uth::AndroidEngine::getInstance().surface);
    }
}