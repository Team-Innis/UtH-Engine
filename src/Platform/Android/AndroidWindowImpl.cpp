#include <UtH/Platform/Android/AndroidWindowImpl.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Android/AndroidEngine.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Engine/Engine.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/Android/InputSensor.hpp>


namespace uth
{
	bool AndroidWindowImpl::focusLost = false;

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
		CheckGLError("eglGetDisplay");

		if(uthAndroidEngine.display == EGL_NO_DISPLAY)
		{
			WriteError("display nodisplay");
		}


		eglInitialize(uthAndroidEngine.display,0,0);
			WriteLog("eglInitialize succeeded");
		CheckGLError("eglInitialize");

		//eglChooseConfig(androidengine.display, attribs, 0, 1, &numConfigs);
		//WriteLog("Configs: %d", (int)numConfigs);

		eglChooseConfig(uthAndroidEngine.display, attribs, &uthAndroidEngine.config, 1, &numConfigs);
		CheckGLError("eglChooseConfig");
			WriteLog("eglChooseConfig succeeded");
		eglGetConfigAttrib(uthAndroidEngine.display, uthAndroidEngine.config, EGL_NATIVE_VISUAL_ID, &format);
		CheckGLError("eglGetConfigAttrib");
			WriteLog("eglGetConfigAttrib succeeded");



		//ANativeWindow_setBuffersGeometry(androidengine.app->window, 0, 0, 0);
		//CheckGLError();
		//	WriteLog("ANativeWindow_setBuffersGeometry succeeded");

		uthAndroidEngine.surface = eglCreateWindowSurface(uthAndroidEngine.display, uthAndroidEngine.config, uthAndroidEngine.app->window, 0);
		CheckGLError("eglCreateWindowSurface");
			WriteLog("eglCreateWindowSurface succeeded");
		uthAndroidEngine.context = eglCreateContext(uthAndroidEngine.display, uthAndroidEngine.config, EGL_NO_CONTEXT, attribList);
		CheckGLError("eglCreateContext");
			WriteLog("eglCreateContext succeeded");

		if(eglMakeCurrent(uthAndroidEngine.display, uthAndroidEngine.surface, uthAndroidEngine.surface, uthAndroidEngine.context) == EGL_FALSE)
		{
			CheckGLError("eglMakeCurrent");
			WriteError("eglMakeCurrent failed");
			return nullptr;
		}

		EGLint tempX;
		EGLint tempY;

		eglQuerySurface(uthAndroidEngine.display, uthAndroidEngine.surface, EGL_WIDTH, &tempX);
		CheckGLError("eglQuerySurface");
		eglQuerySurface(uthAndroidEngine.display, uthAndroidEngine.surface, EGL_HEIGHT, &tempY);
		CheckGLError("eglQuerySurface");

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


	void AndroidWindowImpl::clear(
		const float r,
		const float g,
		const float b,
		const float a,
		const bool clearDepth,
		const bool clearStencil)
	{
		oglCheck(glClear(
			GL_COLOR_BUFFER_BIT |
			GL_DEPTH_BUFFER_BIT |
			GL_STENCIL_BUFFER_BIT
			));
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
			uthAndroidEngine.initialized = true;
			uthAndroidEngine.winEveHand(window);
			if (!focusLost)
				uthEngine.Init(uthAndroidEngine.settings);
			else
			{
				uthRS.PauseSounds();
			}
			uthRS.RecreateOpenGLContext();
			WriteLog("uthAndroidEngine.winEveHand");
			break;
		case APP_CMD_TERM_WINDOW:
			uthAndroidEngine.initialized = false;
			window->destroy();
			return true;
			break;
        case APP_CMD_GAINED_FOCUS:
            uthAndroidEngine.initialized = true;
            uth::SensorInput::GainFocus();
            break;
		case APP_CMD_LOST_FOCUS:
			WriteLog("LostFocus");
			uthAndroidEngine.initialized = false;
			uthRS.ClearOpenGLContext();
			uthRS.PauseSounds();
			focusLost = true;
            uth::SensorInput::LostFocus();
			break;
		}

		return false;
	}

    void AndroidWindowImpl::setResizeCallback(ResizeFunc)
    { }
}