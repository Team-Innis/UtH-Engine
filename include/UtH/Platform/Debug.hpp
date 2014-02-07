#include <assert.h>
#include <iostream>

#include <GL\freeglut.h>
#include <AL\al.h>
#include <AL\alc.h>


void PrintGLString(const char* name, GLenum s)
{
	const char *v = (const char *) glGetString(s);

	printf("GL %s = %s\n", name, v);
}


void CheckGLError(const char* op)
{
	for (GLint error = glGetError(); error; error
		= glGetError()) {
			
			printf("after %s() glError (0x%x)\n", op, error);
	}
}

// FIXME: load the openal libray somewhere to make this work
void CheckALError(const char* op)
{
	//for(ALCenum error = alGetError(); error != AL_NO_ERROR; error = alGetError())
	//{

	//	printf("after %s() glError (0x%x)\n", op, error);
	//}
}


void Win32Assert(int expression)
{
	assert(expression);
}


void WriteLog(const char* text, ...)
{
	va_list v;
	va_start(v, text);
	

	vprintf(text, v);
	va_end(v);
}
