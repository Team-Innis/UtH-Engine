#include <UtH/Platform/Android/AndroidWindowImpl.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Graphics.hpp>


namespace uth
{

    void* AndroidWindowImpl::create(const WindowSettings& settings)
    {

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

		uthAndroidEngine.display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		WriteLog("eglGetDisplay %d", (int)uthAndroidEngine.display);
		CheckEGLError();

		if(uthAndroidEngine.display == EGL_NO_DISPLAY)
		{
			WriteError("display nodisplay");
		}


		eglInitialize(uthAndroidEngine.display,0,0);
			WriteLog("eglInitialize succeeded");
		CheckEGLError();

		//eglChooseConfig(androidengine.display, attribs, NULL, 1, &numConfigs);
		//WriteLog("Configs: %d", (int)numConfigs);

		eglChooseConfig(uthAndroidEngine.display, attribs, &uthAndroidEngine.config, 1, &numConfigs);
		CheckEGLError();
			WriteLog("eglChooseConfig succeeded");
		eglGetConfigAttrib(uthAndroidEngine.display, uthAndroidEngine.config, EGL_NATIVE_VISUAL_ID, &format);
		CheckEGLError();
			WriteLog("eglGetConfigAttrib succeeded");



		//ANativeWindow_setBuffersGeometry(androidengine.app->window, 0, 0, 0);
		//CheckEGLError();
		//	WriteLog("ANativeWindow_setBuffersGeometry succeeded");

		uthAndroidEngine.surface = eglCreateWindowSurface(uthAndroidEngine.display, uthAndroidEngine.config, uthAndroidEngine.app->window, NULL);
		CheckEGLError();
			WriteLog("eglCreateWindowSurface succeeded");
		uthAndroidEngine.context = eglCreateContext(uthAndroidEngine.display, uthAndroidEngine.config, EGL_NO_CONTEXT, attribList);
		CheckEGLError();
			WriteLog("eglCreateContext succeeded");

		if(eglMakeCurrent(uthAndroidEngine.display, uthAndroidEngine.surface, uthAndroidEngine.surface, uthAndroidEngine.context) == EGL_FALSE)
		{
			CheckEGLError();
			WriteError("eglMakeCurrent failed");
			return (void*)NULL;
		}

		EGLint tempX;
		EGLint tempY;

		eglQuerySurface(uthAndroidEngine.display, uthAndroidEngine.surface, EGL_WIDTH, &tempX);
		CheckEGLError();
		eglQuerySurface(uthAndroidEngine.display, uthAndroidEngine.surface, EGL_HEIGHT, &tempY);
		CheckEGLError();

		uthAndroidEngine.settings.size.x = static_cast<float>(tempX);
		uthAndroidEngine.settings.size.y = static_cast<float>(tempY);
		const_cast<WindowSettings&>(settings).size = uthAndroidEngine.settings.size;

		//glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
		//glEnable(GL_CULL_FACE);
		//glEnable(GL_DEPTH_TEST);
		Graphics::SetBlendFunction(true, SRC_ALPHA, ONE_MINUS_SRC_ALPHA);

		WriteLog("+++++++++++++++++++++++++++++++++++++++");
		WriteLog((const char*)glGetString(GL_VERSION));
		WriteLog("+++++++++++++++++++++++++++++++++++++++");

		return nullptr;
    }


    void* AndroidWindowImpl::destroy(void* handle)
    {

        if(uthAndroidEngine.display != EGL_NO_DISPLAY)
		{
			eglMakeCurrent(uthAndroidEngine.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			if(uthAndroidEngine.display != EGL_NO_DISPLAY)
			{
				eglDestroyContext(uthAndroidEngine.display, uthAndroidEngine.context);
			}
			if (uthAndroidEngine.surface != EGL_NO_SURFACE)
			{
				eglDestroySurface(uthAndroidEngine.display, uthAndroidEngine.surface);
			}
			eglTerminate(uthAndroidEngine.display);
		}
		uthAndroidEngine.display = EGL_NO_DISPLAY;
		uthAndroidEngine.context = EGL_NO_CONTEXT;
		uthAndroidEngine.surface = EGL_NO_SURFACE;

		uthAndroidEngine.initialized = false;

		WriteLog("Window Destroyed");

		return nullptr;
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

	bool AndroidWindowImpl::processMessages(void* handle)
	{
		android_app* app = uthAndroidEngine.app;
		uth::Window* window = ((uth::Window*)app->userData);

		switch (uthAndroidEngine.message)
		{
		case APP_CMD_SAVE_STATE:
			WriteLog("SaveStated");
			break;
		case APP_CMD_INIT_WINDOW:
			WriteLog("windowINIT");
			uthEngine.Init(uthAndroidEngine.settings);
			uthAndroidEngine.initialized = true;
			uthAndroidEngine.winEveHand(window);
			WriteLog("uthAndroidEngine.winEveHand");
			break;
		case APP_CMD_TERM_WINDOW:
			uthAndroidEngine.initialized = false;
			window->destroy();
			return true;
			break;
		case APP_CMD_GAINED_FOCUS:
			uthAndroidEngine.initialized = true;
			break;
		case APP_CMD_LOST_FOCUS:
			WriteLog("LostFocus");
			uthAndroidEngine.initialized = false;
			break;
		}

		return false;
	}
}