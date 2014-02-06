#include <UtH\Platform\Configuration.hpp>



#if defined(UTH_SYSTEM_WINDOWS)

    #include <GL\glew.h>
    #include <GL\freeglut.h>
    #include <GL\glut.h>

#elif defined(UTH_SYSTEM_LINUX)

    #include <GL\GL.h>
    #include <GL\GLU.h>

#elif defined(UTH_SYSTEM_MACOS)

    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>

#elif defined(UTH_SYSTEM_ANDROID)

    #include <GLES/gl.h>
    #include <GLES/glu.h>
    #include <GL\freeglut.h>
    #include <GL\glut.h>

#elif defined(UTH_SYSTEM_IOS)

    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glu.h>

#endif