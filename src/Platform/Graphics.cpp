#include <UtH\Platform\Graphics.hpp>
#include <UtH\Platform\Configuration.hpp>
#include <UtH\Platform\OpenGL.hpp>
#include <UtH\Platform\OGLCheck.hpp>
#include <iostream>

#pragma comment(lib, "freeglutd.lib")
#pragma comment(lib, "glew32d.lib")


namespace uth
{
    // Window functions
    bool Graphics::createWindow(const WindowSettings& settings)
    {
        if (m_windowHandle) destroyWindow();
        
        m_windowSettings = settings;

        // Context settings
        oglCheck(glutInitContextFlags(GLUT_FORWARD_COMPATIBLE));
        oglCheck(glutInitContextProfile(GLUT_CORE_PROFILE));

        // Extra settings
        oglCheck(glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS));

        // Position & size
        oglCheck(glutInitWindowPosition(settings.position.x, settings.position.y));
        oglCheck(glutInitWindowSize(settings.size.x, settings.size.y));

        // Display settings
        oglCheck(glutInitDisplayMode(settings.useBlending ? GLUT_RGBA : GLUT_RGB |
                            settings.useDepthBuffer ? GLUT_DEPTH : 0x0 |
                            settings.useStencilBuffer ? GLUT_STENCIL : 0x0 |
                            settings.useDoubleBuffering ? GLUT_DOUBLE : GLUT_SINGLE));


        int majorVer = settings.contextVersionMajor,
            minorVer = settings.contextVersionMinor;
        
        oglCheck(glutInitContextVersion(settings.contextVersionMajor, settings.contextVersionMinor));

        m_windowHandle = glutCreateWindow("Generic Window Title");
        
        return true;
    }


    void Graphics::destroyWindow()
    {
        oglCheck(glutDestroyWindow(m_windowHandle));
    }


    void Graphics::clear(const float r, const float g, const float b, const float a)
    {
        oglCheck(glClear(GL_COLOR_BUFFER_BIT |
                         GL_DEPTH_BUFFER_BIT |
                         GL_STENCIL_BUFFER_BIT));
		oglCheck(glClearColor(r, g, b, a));

        if (!m_windowSettings.useDepthBuffer) return;

		#ifdef UTH_SYSTEM_OPENGLES
			oglCheck(glClearDepthf(1)); 
		#else
			oglCheck(glClearDepth(1)); 
		#endif

        if (!m_windowSettings.useStencilBuffer) return;

        oglCheck(glClearStencil(1));
    }

    void Graphics::swapBuffers()
    {
        oglCheck(glutSwapBuffers());
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Shaders

    int Graphics::createShaderProgram()
    {
        return glCreateProgram();
    }

    bool Graphics::createShader(const Graphics::ShaderType type, const int shaderProgram, const char* shaderCode)
    {
        if (!shaderCode) return false;

        static int shaderTypes[Graphics::ShaderType::SHADER_LAST] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER};


        unsigned int shader = glCreateShader(shaderTypes[type]);

        oglCheck(glShaderSource(shader, 1, &shaderCode, NULL));
        oglCheck(glCompileShader(shader));

        int success;
		oglCheck(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

		if (!success)
		{
            glDeleteShader(shader);

            return false;
        }

        oglCheck(glAttachShader(shaderProgram, shader));
        oglCheck(glDeleteShader(shader));

        return true;
    }

    bool Graphics::linkShaderProgram(const int shaderProgram)
    {
        oglCheck(glLinkProgram(shaderProgram));

        int success;
		oglCheck(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));

		if (!success)
		{
            destroyShaderProgram(shaderProgram);

			return false;
		}

		return true;
    }

    void Graphics::bindProgram(const int shaderProgram)
    {
        if (shaderProgram)
            oglCheck(glUseProgram(shaderProgram));
    }

    void Graphics::destroyShaderProgram(const int shaderProgram)
    {
        oglCheck(glDeleteProgram(shaderProgram));
    }

    int Graphics::getUniformLocation(const int shaderProgram, const char* name)
    {
		return glGetUniformLocation(shaderProgram, name);
    }

    int Graphics::getAttributeLocation(const int shaderProgram, const char* name)
    {
        return glGetAttribLocation(shaderProgram, name);
    }

    void Graphics::setUniform(const int location, const float x)
    {
        oglCheck(glUniform1f(location, x));
    }

    void Graphics::setUniform(const int location, const float x, const float y)
    {
        oglCheck(glUniform2f(location, x, y));
    }

    void Graphics::setUniform(const int location, const float x, const float y, const float z)
    {
        oglCheck(glUniform3f(location, x, y, z));
    }

    void Graphics::setUniform(const int location, const float x, const float y, const float z, const float w)
    {
        oglCheck(glUniform4f(location, x, y, z, w));
    }

    void Graphics::setUniform(const int location, const umath::vector2& vector)
    {
        oglCheck(glUniform2fv(location, 1, &vector.x));
    }

    void Graphics::setUniform(const int location, const umath::vector3& vector)
    {
        oglCheck(glUniform3fv(location, 1, &vector.x));
    }

    void Graphics::setUniform(const int location, const umath::vector4& vector)
    {
        oglCheck(glUniform4fv(location, 1, &vector.x));
    }

    void Graphics::setUniform(const int location, const umath::matrix3& matrix)
    {
        oglCheck(glUniformMatrix3fv(location, 1, GL_FALSE, &matrix[0][0]));
    }

    void Graphics::setUniform(const int location, const umath::matrix4& matrix)
    {
        oglCheck(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
    }

    void Graphics::enableVertexAttribArray(const int location)
    {
        oglCheck(glEnableVertexAttribArray(location));
    }

    void Graphics::disableVertexAttribArray(const int location)
    {
        oglCheck(glDisableVertexAttribArray(location));
    }

    void Graphics::setVertexAttribPointer(const int location, const int size, const DataType type, const int stride, void* pointer)
    {
        static int dataTypes[Graphics::DataType::TYPE_LAST] = {GL_FLOAT, GL_INT};


        oglCheck(glVertexAttribPointer(location, size, dataTypes[type], GL_FALSE, stride, pointer));
    }






    // Private

    Graphics::Graphics()
        : m_windowHandle(0),
          m_windowSettings()
    {
        char* myargv[1];
        int myargc = 1;
        myargv[0] = strdup("UtH Engine");
        glutInit(&myargc, myargv);

        glewInit();
    }

    Graphics::~Graphics()
    {
        destroyWindow();
    }
}