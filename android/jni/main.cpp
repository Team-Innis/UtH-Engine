/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <jni.h>
#include <errno.h>
#include <android_native_app_glue.h>

#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/Debug.hpp>

#include <UtH/Math/Math.hpp>


//Struct containing EGL stugg and android app
struct AndroidEngine
{
	android_app* app;


	//Below this to Graphics-classs?
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	EGLConfig config;

	umath::vector2 resolution;
};

//To Graphics init or Renderer class
int displayInit(AndroidEngine* androidengine)
{
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

	androidengine->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(androidengine->display,0,0);

	eglChooseConfig(androidengine->display, attribs, &androidengine->config, 1, &numConfigs);
	eglGetConfigAttrib(androidengine->display, androidengine->config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(androidengine->app->window, 0, 0, format);

	androidengine->surface = eglCreateWindowSurface(androidengine->display, androidengine->surface, androidengine->app->window, NULL);
	androidengine->context = eglCreateContext(androidengine->display, androidengine->config, NULL, attribList);

	if(eglMakeCurrent(androidengine->display, androidengine->surface, androidengine->surface, androidengine->context) == false)
	{
		WriteLog("eglMakeCurrent failed");
		return -1;
	}

	EGLint tempX;
	EGLint tempY;

	eglQuerySurface(androidengine->display, androidengine->surface, EGL_WIDTH, &tempX);
	eglQuerySurface(androidengine->display, androidengine->surface, EGL_HEIGHT, &tempY);

	androidengine->resolution.x = tempX;
	androidengine->resolution.y = tempY;

	glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glViewport(0,0,androidengine->resolution.x,androidengine->resolution.y);

	return 0;
}

void displayDestroy(AndroidEngine* androidengine)
{
	if(androidengine->display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(androidengine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if(androidengine->display != EGL_NO_DISPLAY)
		{
			eglDestroyContext(androidengine->display, androidengine->context);
		}
		if (androidengine->surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(androidengine->display, androidengine->surface);
		}
		eglTerminate(androidengine->display);
	}
	androidengine->display = EGL_NO_DISPLAY;
	androidengine->context = EGL_NO_CONTEXT;
	androidengine->surface = EGL_NO_SURFACE;
}

//After input manager 
int handle_input(android_app* app, AInputEvent* event)
{
	AndroidEngine* androidengine = (AndroidEngine*)app->userData;
	//Input should be places here
	return 0;
}

void draw_frame(AndroidEngine* androidengine)
{

}

//This is sort of state manager. Checks is Activity on top or not and does it have saved state
void handle_cmd(android_app* app, int cmd)
{
	AndroidEngine* androidengine = (AndroidEngine*)app->userData;

	switch (cmd)
	{
	case APP_CMD_SAVE_STATE:
		break;
	case APP_CMD_INIT_WINDOW:
		if (androidengine->app->window != NULL)
		{
			displayInit(androidengine);
			draw_frame(androidengine);
		}
		break;
	case APP_CMD_TERM_WINDOW:
		displayDestroy(androidengine);
		break;
	case APP_CMD_LOST_FOCUS:
		draw_frame(androidengine);
		break;
	}
}

void android_main(android_app* state)
{
	AndroidEngine androidengine;

	app_dummy();

	memset(&androidengine, 0, sizeof(AndroidEngine));

	state->userData = &androidengine;
	state->onAppCmd = handle_cmd;
	state->onInputEvent = handle_input;

	androidengine.app = state;

	while(1)
	{
		int ident;
		int events;
		android_poll_source* source;

		while ((ident=ALooper_pollAll(0, NULL, &events,(void**)&source)) >= 0)
		{
			//Insteads of these two 'if' statement proper exit should be placed
			if (source != NULL)
			{
				source->process(state, source);
			}
			if (state->destroyRequested != 0)
			{
				displayDestroy(&androidengine);
				return;
			}
		}

		if(androidengine.display == NULL)
		{
			;//Do nothing
		}
		else
		{
			//engine->Update();
		}
	}
}