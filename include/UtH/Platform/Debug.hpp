#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include <UtH/Platform/OpenGL.hpp>

#include <assert.h>
#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>

#if defined(UTH_SYSTEM_ANDROID)
	#include <android/log.h>
	#ifndef LOG_TAG
		#define LOG_TAG	"uth-engine"
	#endif
	#ifndef LOGI
		#define LOGI(...)	__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
	#endif
	#ifndef LOGE
		#define LOGE(...)	__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
	#endif
	static void WriteLog(const char* text, ...)
	{
		va_list v;
		va_start(v, text);
		__android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, text, v);
		va_end(v);
	}
#elif defined(UTH_SYSTEM_WINDOWS)
	static void WriteLog(const char* text, ...)
	{
		va_list v;
		va_start(v, text);
		vprintf(text, v);
		va_end(v);
	}
#endif

static void PrintGLString(const char* name, GLenum s)
{
	const char *v = (const char *) glGetString(s);

	WriteLog("GL %s = %s\n", name, v);
}

static void CheckGLError(const char* op)
{
	for (GLint error = glGetError(); error; error
		= glGetError()) {
			
			WriteLog("after %s() glError (0x%x)\n", op, error);
	}
}

static void CheckALError(const char* op)
{
	for(ALCenum error = alGetError(); error != AL_NO_ERROR; error = alGetError())
	{

		WriteLog("after %s() glError (0x%x)\n", op, error);
	}
}

static void Win32Assert(int expression)
{
	assert(expression);
}

#endif