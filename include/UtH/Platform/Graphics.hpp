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


        // Shader functions
        enum ShaderType
        {
            VERTEX_SHADER,
            FRAGMENT_SHADER,
            GEOMETRY_SHADER,

            SHADER_LAST
        };


        int createShaderProgram();

        // Creates the shader object, compiles the source and then attaches it to the program object.
        // Does not to the linking.
        bool createShader(const ShaderType type, const int shaderProgram, const char* shaderCode);

        bool linkShaderProgram(const int shaderProgram);

        void bindProgram(const int shaderProgram);

        void destroyShaderProgram(const int shaderProgram);

        int getUniformLocation(const char* name);

        int getAttributeLocation(const char* name);

        //bool setUniform(const umath::



    private:

        Graphics();

        ~Graphics();



        int m_windowHandle;
        WindowSettings m_windowSettings;

    };
}