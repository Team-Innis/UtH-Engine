#pragma once
#ifndef _ANDROIDENGINE_H_UTH
#define _ANDROIDENGINE_H_UTH

#include <UtH/Platform/Singleton.hpp>
#include <UtH/Platform/WindowSettings.hpp>
#include <UtH/Platform/Window.hpp>

#include <jni.h>
#include <errno.h>
#include <android_native_app_glue.h>

#define uthAndroidEngine uth::AndroidEngine::getInstance()

namespace uth
{
//Struct containing EGL stugg and android app
class AndroidEngine : public Singleton<AndroidEngine>
{
	friend class Singleton<AndroidEngine>;
private:
	AndroidEngine(){}
	~AndroidEngine(){}
public:
	bool initialized;

	android_app* app;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	EGLConfig config;

	int message;

	uth::WindowSettings settings;

	Window* window;
	
	typedef void (*WindowEventHandler)(void* handle);
	WindowEventHandler winEveHand;
};
}

#endif