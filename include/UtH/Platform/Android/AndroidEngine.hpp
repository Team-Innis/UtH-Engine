#pragma once
#ifndef _ANDROIDENGINE_H_UTH
#define _ANDROIDENGINE_H_UTH

#include <UtH/Platform/Singleton.hpp>
#include <UtH/Platform/WindowSettings.hpp>

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
	android_app* app;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	EGLConfig config;

	int message;

	uth::WindowSettings settings;
	bool initialized;
};
}

#endif