#pragma once
#ifndef OPENGL_H_UTH
#define OPENGL_H_UTH

#include <UtH/Platform/Configuration.hpp>



#if defined(UTH_SYSTEM_WINDOWS)

    #include <GL/glew.h>
    #include <GLFW/glfw3.h>

#elif defined(UTH_SYSTEM_LINUX)

    #include <GL/glew.h>
    #include <GLFW/glfw3.h>

#elif defined(UTH_SYSTEM_MACOS)

    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>

#elif defined(UTH_SYSTEM_ANDROID)

	#include <EGL/egl.h>
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>

#elif defined(UTH_SYSTEM_IOS)

    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glu.h>

#endif

#endif