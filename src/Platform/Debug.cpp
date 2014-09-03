#include <UtH/Platform/Debug.hpp>

#include <UtH/Platform/OpenGL.hpp>

#include <assert.h>
#include <iostream>
#include <cstdio>

#include <AL/al.h>
#include <AL/alc.h>

#ifdef UTH_SYSTEM_ANDROID

    #include <android/log.h>
    #include <gl/egl.h>
    #ifndef LOG_TAG
        #define LOG_TAG	"uth-engine"
    #endif

#endif


void WriteError(const char* text, ...)
{
    #if defined(UTH_SYSTEM_ANDROID)

        va_list v;
        va_start(v, text);
        __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, text, v);
        va_end(v);

    #else

        printf(
            "\n********ERROR********"
            "\n");

        va_list v;
        va_start(v, text);
        vprintf(text, v);
        va_end(v);

        printf(
            "\n*********************"
            "\n\n");

        //assert(false);  //GL_INVALID_ENUM would crash

    #endif
}

void WriteWarning(const char* text, ...)
{
    #if defined (UTH_SYSTEM_ANDROID)

        va_list v;
        va_start(v, text);
        __android_log_vprint(ANDROID_LOG_WARN, LOG_TAG, text, v);
        va_end(v);

    #else

        printf(
            "\n-------WARNING-------"
            "\n");

        va_list v;
        va_start(v, text);
        vprintf(text, v);
        va_end(v);

        printf(
            "\n---------------------"
            "\n\n");

    #endif
}

void WriteLog(const char* text, ...)
{
    #if defined (UTH_SYSTEM_ANDROID)

        va_list v;
        va_start(v, text);
        __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, text, v);
        va_end(v);

    #else

        va_list v;
        va_start(v, text);
        vprintf(text, v);
        va_end(v);

    #endif
}

void PrintGLString(const char* name, GLenum s)
{
    #if defined(UTH_SYSTEM_OPENGL) 

        const char *v = (const char *)glGetString(s);

        WriteLog("GL %s = %s\n", name, v);

    #else

        name;
        s;

    #endif
}

void CheckGLError(const char* op)
{
    #if defined (UTH_SYSTEM_ANDROID)

        EGLint error = eglGetError();
        if (error != EGL_SUCCESS)
        {
            WriteWarning("EGL Function Failed: %d\n", error);
        }

    #else

        for (GLint error = glGetError(); error; error
             = glGetError()) {

            WriteError("after %s() glError (0x%x)", op, error);
        }

    #endif
}

void CheckALError(const char* op)
{
    for (ALCenum error = alGetError(); error != ALC_NO_ERROR; error = alGetError())
    {
        WriteError("after %s() alError (0x%x)", op, error);
    }
}

