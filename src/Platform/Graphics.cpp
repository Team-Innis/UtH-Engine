#include <UtH\Platform\Graphics.hpp>
#include <UtH\Platform\Configuration.hpp>
#include <UtH\Platform\OpenGL.hpp>
#include <UtH\Platform\OGLCheck.hpp>
#include <iostream>

#ifdef _DEBUG
#pragma comment(lib, "freeglut_staticd.lib")
#pragma comment(lib, "glew32sd.lib")
#else // Release
// FIXME: Static 'Release' version of the GLEW lib breaks the build
// consider using dynamic linking for release
#pragma comment(lib, "freeglut_static.lib")
#pragma comment(lib, "glew32sd.lib")
#endif

namespace uth
{
    static int shaderTypes[SHADERTYPE_LAST] =           {GL_VERTEX_SHADER,
                                                         GL_FRAGMENT_SHADER};
    static int dataTypes[DATATYPE_LAST] =               {GL_BYTE,
                                                         GL_UNSIGNED_BYTE,
                                                         GL_SHORT,
                                                         GL_UNSIGNED_SHORT,
                                                         GL_INT,
                                                         GL_UNSIGNED_INT,
                                                         GL_FLOAT,
                                                         GL_DOUBLE};
    static int bufferTypes[BUFFERTYPE_LAST] =           {GL_ARRAY_BUFFER,
                                                         GL_READ_BUFFER,
                                                         GL_COPY_WRITE_BUFFER,
                                                         GL_ELEMENT_ARRAY_BUFFER,
                                                         GL_PIXEL_PACK_BUFFER,
                                                         GL_PIXEL_UNPACK_BUFFER,
                                                         GL_TEXTURE_BUFFER,
                                                         GL_TRANSFORM_FEEDBACK_BUFFER,
                                                         GL_UNIFORM_BUFFER};
    static int usageTypes[USAGETYPE_LAST] =             {GL_STREAM_DRAW,
                                                         GL_STREAM_READ,
                                                         GL_STREAM_COPY,
                                                         GL_STATIC_DRAW,
                                                         GL_STATIC_READ,
                                                         GL_STATIC_COPY,
                                                         GL_DYNAMIC_DRAW,
                                                         GL_DYNAMIC_READ,
                                                         GL_DYNAMIC_COPY};
    static int pixelStoreParams[PIXELSTOREPARAM_LAST] = {GL_PACK_SWAP_BYTES,
                                                         GL_PACK_LSB_FIRST, 
                                                         GL_PACK_ROW_LENGTH, 
                                                         GL_PACK_IMAGE_HEIGHT, 
                                                         GL_PACK_SKIP_PIXELS, 
                                                         GL_PACK_SKIP_ROWS, 
                                                         GL_PACK_SKIP_IMAGES, 
                                                         GL_PACK_ALIGNMENT,
                                                         GL_UNPACK_SWAP_BYTES, 
                                                         GL_UNPACK_LSB_FIRST, 
                                                         GL_UNPACK_ROW_LENGTH, 
                                                         GL_UNPACK_IMAGE_HEIGHT, 
                                                         GL_UNPACK_SKIP_PIXELS, 
                                                         GL_UNPACK_SKIP_ROWS, 
                                                         GL_UNPACK_SKIP_IMAGES, 
                                                         GL_UNPACK_ALIGNMENT};
    static int textureTypes[TEXTURETYPE_LAST] =         {TEXTURE_1D, 
                                                         TEXTURE_2D, 
                                                         TEXTURE_3D, 
                                                         TEXTURE_1D_ARRAY, 
                                                         TEXTURE_2D_ARRAY, 
                                                         TEXTURE_RECTANGLE, 
                                                         TEXTURE_CUBE_MAP,
                                                         TEXTURE_2D_MULTISAMPLE,
                                                         TEXTURE_2D_MULTISAMPLE_ARRAY};
    static int imageFormats[IMAGEFORMAT_LAST] =         {GL_RGB,
                                                         GL_RGBA};
    static int textureParams[TEXTUREPARAM_LAST] =       {GL_TEXTURE_BASE_LEVEL, 
                                                         GL_TEXTURE_COMPARE_FUNC, 
                                                         GL_TEXTURE_COMPARE_MODE, 
                                                         GL_TEXTURE_LOD_BIAS, 
                                                         GL_TEXTURE_MIN_FILTER, 
                                                         GL_TEXTURE_MAG_FILTER, 
                                                         GL_TEXTURE_MIN_LOD, 
                                                         GL_TEXTURE_MAX_LOD, 
                                                         GL_TEXTURE_MAX_LEVEL, 
                                                         GL_TEXTURE_SWIZZLE_R, 
                                                         GL_TEXTURE_SWIZZLE_G, 
                                                         GL_TEXTURE_SWIZZLE_B, 
                                                         GL_TEXTURE_SWIZZLE_A, 
                                                         GL_TEXTURE_WRAP_S, 
                                                         GL_TEXTURE_WRAP_T,
                                                         GL_TEXTURE_WRAP_R};
    static int primitiveTypes[PRIMITIVETYPE_LAST] =     {GL_POINTS, 
                                                         GL_LINE_STRIP, 
                                                         GL_LINE_LOOP, 
                                                         GL_LINES, 
                                                         GL_LINE_STRIP_ADJACENCY, 
                                                         GL_LINES_ADJACENCY, 
                                                         GL_TRIANGLE_STRIP, 
                                                         GL_TRIANGLE_FAN, 
                                                         GL_TRIANGLES, 
                                                         GL_TRIANGLE_STRIP_ADJACENCY,
                                                         GL_TRIANGLES_ADJACENCY};
    static int depthFunctions[DEPTHFUNCTION_LAST] =     {GL_NEVER, 
                                                         GL_LESS, 
                                                         GL_EQUAL, 
                                                         GL_LEQUAL,
                                                         GL_GREATER, 
                                                         GL_NOTEQUAL, 
                                                         GL_GEQUAL, 
                                                         GL_ALWAYS};
    static int blendFunctions[BLENDFUNCTION_LAST] =     {GL_ZERO, 
                                                         GL_ONE, 
                                                         GL_SRC_COLOR, 
                                                         GL_ONE_MINUS_SRC_COLOR, 
                                                         GL_DST_COLOR, 
                                                         GL_ONE_MINUS_DST_COLOR, 
                                                         GL_SRC_ALPHA, 
                                                         GL_ONE_MINUS_SRC_ALPHA, 
                                                         GL_DST_ALPHA, 
                                                         GL_ONE_MINUS_DST_ALPHA, 
                                                         GL_CONSTANT_COLOR, 
                                                         GL_ONE_MINUS_CONSTANT_COLOR, 
                                                         GL_CONSTANT_ALPHA, 
                                                         GL_ONE_MINUS_CONSTANT_ALPHA};
    static int faceCullings[FACECULLING_LAST] =         {GL_FRONT, 
                                                         GL_BACK, 
                                                         GL_FRONT_AND_BACK};

    

    // Window functions
    bool Graphics::createWindow(const WindowSettings& settings)
    {
        if (m_windowHandle) destroyWindow();
        
        m_windowSettings = settings;

        // Context settings
        glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
        glutInitContextProfile(GLUT_CORE_PROFILE);

        // Extra settings
        glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

        // Position & size
        glutInitWindowPosition(settings.position.x, settings.position.y);
        glutInitWindowSize(settings.size.x, settings.size.y);

        // Display settings
        glutInitDisplayMode(settings.useBlending ? GLUT_RGBA : GLUT_RGB |
                            settings.useDepthBuffer ? GLUT_DEPTH : 0x0 |
                            settings.useStencilBuffer ? GLUT_STENCIL : 0x0 |
                            settings.useDoubleBuffering ? GLUT_DOUBLE : GLUT_SINGLE);


        int majorVer = settings.contextVersionMajor,
            minorVer = settings.contextVersionMinor;
        
        glutInitContextVersion(settings.contextVersionMajor, settings.contextVersionMinor);

        m_windowHandle = glutCreateWindow("Generic Window Title");

        glewInit();
        
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

    void setViewport(const int x, const int y, const size_t width, const size_t height)
    {
        oglCheck(glViewport(x, y, width, height));
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Shaders

    int Graphics::createShaderProgram()
    {
        return glCreateProgram();
    }

    bool Graphics::createShader(const ShaderType type, const int shaderProgram, const char* shaderCode)
    {
        if (!shaderCode) return false;

        unsigned int shader = glCreateShader(shaderTypes[type]);

        oglCheck(glShaderSource(shader, 1, &shaderCode, NULL));
        oglCheck(glCompileShader(shader));

		int infoLenght;
		oglCheck(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLenght));
		if(infoLenght > 1)
		{
			char* buf = new char[infoLenght];
			oglCheck(glGetShaderInfoLog(shader, infoLenght, NULL, buf));
			std::cout << buf << std::endl;
			delete buf;
		}

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

    void unbindProgram()
    {
        oglCheck(glUseProgram(0));
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

    void Graphics::setVertexAttribPointer(const int location, const int size, DataType type, const int stride, const void* pointer)
    {
        oglCheck(glVertexAttribPointer(location, size, dataTypes[type], GL_FALSE, stride, pointer));
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Buffers

    void generateBuffers(const unsigned int amount, unsigned int* buffers)
    {
        oglCheck(glGenBuffers(amount, buffers));
    }

    void deleteBuffers(const unsigned int amount, unsigned int* buffers)
    {
        oglCheck(glDeleteBuffers(amount, buffers));
    }

    void bindBuffer(BufferType type, const unsigned int buffer)
    {
        oglCheck(glBindBuffer(bufferTypes[type], buffer));
    }

    void setBufferData(BufferType type, const unsigned int size, const void* data, UsageType usageType)
    {
        oglCheck(glBufferData(bufferTypes[type], size, data, usageTypes[usageType]));
    }

    void setBufferSubData(BufferType type, const unsigned int offset, const unsigned int size, const void* data)
    {
        oglCheck(glBufferSubData(bufferTypes[type], offset, size, data));
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Texture functions
        
    void setPixelStore(PixelStoreParam param, const int value)
    {
        oglCheck(glPixelStorei(pixelStoreParams[param], value));
    }

    void generateTextures(const unsigned int amount, unsigned int* data)
    {
        oglCheck(glGenTextures(amount, data));
    }

    void setActiveTexUnit(TexUnit unit)
    {
        oglCheck(glActiveTexture(unit));
    }

    void bindTexture(TextureType type, const int texture)
    {
        oglCheck(glBindTexture(textureTypes[type], texture));
    }

    void setTextureImage1D(const int level, ImageFormat imageFormat, const size_t width, ImageFormat pixelFormat, DataType dataType, const void* pixels)
    {
        oglCheck(glTexImage1D(textureTypes[TEXTURE_1D], level, imageFormats[imageFormat], width, 0, imageFormats[pixelFormat], dataTypes[dataType], pixels));
    }

    void setTextureImage2D(TextureType type, const int level, ImageFormat imageFormat, const size_t width, const size_t height, ImageFormat pixelFormat, DataType dataType, const void* pixels)
    {
        oglCheck(glTexImage2D(textureTypes[TEXTURE_2D], level, imageFormats[imageFormat], width, height, 0, imageFormats[pixelFormat], dataTypes[dataType], pixels));
    }

    void setTextureParameter(TextureType type, TextureParam param, const int value)
    {
        oglCheck(glTexParameteri(textureTypes[type], textureParams[param], value));
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Drawing functions
    void drawArrays(PrimitiveType type, const int first, const size_t count)
    {
        oglCheck(glDrawArrays(primitiveTypes[type], first, count));
    }

    void drawElements(PrimitiveType type, const size_t count, DataType dataType, const void* indices)
    {
        oglCheck(glDrawElements(primitiveTypes[type], count, dataTypes[dataType], indices));
    }

    void setPointSize(const float size)
    {
        oglCheck(glPointSize(size));
    }

    void setLineWidth(const float width)
    {
        oglCheck(glLineWidth(width));
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    // Other
    void flush()
    {
        oglCheck(glFlush());
    }

    void setDepthFunction(const bool enable, DepthFunction func)
    {
        static bool enabled = false;

        if (enable != enabled)
        {
            if (enable)
                oglCheck(glEnable(GL_DEPTH_TEST));
            else
                oglCheck(glDisable(GL_DEPTH_TEST));

            enabled = !enabled;
        }

        oglCheck(glDepthFunc(depthFunctions[func]));
    }

    void setBlendFunction(const bool enable, BlendFunction sfunc, BlendFunction dfunc)
    {
        static bool enabled = false;

        if (enable != enabled)
        {
            if (enable)
                oglCheck(glEnable(GL_BLEND));
            else
                oglCheck(glDisable(GL_BLEND));

            enabled = !enabled;
        }

        oglCheck(glBlendFunc(blendFunctions[sfunc], blendFunctions[dfunc]));
    }

    void setFaceCulling(const bool enable, FaceCulling mode)
    {
        static bool enabled = false;

        if (enable != enabled)
        {
            if (enable)
                oglCheck(glEnable(GL_CULL_FACE));
            else
                oglCheck(glDisable(GL_CULL_FACE));

            enabled = !enabled;
        }

        oglCheck(glCullFace(faceCullings[mode]));
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
    }

    Graphics::~Graphics()
    {
        destroyWindow();
    }
}