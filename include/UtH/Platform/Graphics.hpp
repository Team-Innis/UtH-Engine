#pragma once

#include <UtH\Platform\WindowSettings.hpp>
#include <UtH\Platform\Singleton.hpp>
#include <UtH\Math\Math.hpp>


#define uthGraphics uth::Graphics::getInstance()


namespace uth
{

    class Graphics : public uth::Singleton<uth::Graphics>
    {

        friend class Singleton<uth::Graphics>;


    public:

        // Window functions
        bool createWindow(const WindowSettings& settings);

        void destroyWindow();

        void clear(const float r, const float g, const float b, const float a = 1.f);

        void swapBuffers();


        /////////////////////////////////////////////////////////
        // Shader functions
        enum ShaderType
        {
            VERTEX_SHADER,
            FRAGMENT_SHADER,
            GEOMETRY_SHADER,

            SHADER_LAST
        };

        enum DataType
        {
            FLOAT_TYPE,
            INT_TYPE,

            TYPE_LAST
        };


        int createShaderProgram();

        // Creates the shader object, compiles the source and then attaches it to the program object.
        // Does not to the linking.
        bool createShader(const ShaderType type, const int shaderProgram, const char* shaderCode);

        bool linkShaderProgram(const int shaderProgram);

        void bindProgram(const int shaderProgram);

        void destroyShaderProgram(const int shaderProgram);

        int getUniformLocation(const int shaderProgram, const char* name);

        int getAttributeLocation(const int shaderProgram, const char* name);

        void setUniform(const int location, const float x);

        void setUniform(const int location, const float x, const float y);

        void setUniform(const int location, const float x, const float y, const float z);

        void setUniform(const int location, const float x, const float y, const float z, const float w);

        void setUniform(const int location, const umath::vector2& vector);

        void setUniform(const int location, const umath::vector3& vector);

        void setUniform(const int location, const umath::vector4& vector);

        void setUniform(const int location, const umath::matrix3& matrix);

        void setUniform(const int location, const umath::matrix4& matrix);

        void enableVertexAttribArray(const int location);

        void disableVertexAttribArray(const int location);

        void setVertexAttribPointer(const int location, const int size, const DataType type, const int stride, void* pointer);


        /////////////////////////////////////////////////////////
        // Buffer functions




        /////////////////////////////////////////////////////////
        // Texture functions



    private:

        Graphics();

        ~Graphics();



        int m_windowHandle;
        WindowSettings m_windowSettings;

    };
}