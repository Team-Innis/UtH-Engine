#pragma once

#include <UtH\Platform\WindowSettings.hpp>
#include <UtH\Platform\Singleton.hpp>
#include <UtH\Platform\Enums.hpp>
#include <UtH\Math\Math.hpp>


#define uthGraphics uth::Graphics::getInstance()


namespace uth
{

    class Graphics : public uth::Singleton<uth::Graphics>
    {

        friend class Singleton<uth::Graphics>;


    public:

        /////////////////////////////////////////////////////////
        // Window functions
        // Create the window. If a windows has already been created, it's closed and a new one opened.
        // This function assumes that glutInit() has already been called.
        bool createWindow(const WindowSettings& settings);

        void destroyWindow();

        void clear(const float r, const float g, const float b, const float a = 1.f);

        void swapBuffers();


        /////////////////////////////////////////////////////////
        // Shader functions
        int createShaderProgram();

        // Creates the shader object, compiles the source and then attaches it to the program object.
        // Does not do the linking.
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

        void setVertexAttribPointer(const int location, const int size, const DataType type, const int stride, const void* pointer);


        /////////////////////////////////////////////////////////
        // Buffer functions
        void generateBuffers(const unsigned int amount, unsigned int* buffers);

        void deleteBuffers(const unsigned int amount, unsigned int* buffers);

        void bindBuffer(BufferType type, const unsigned int buffer);

        void setBufferData(BufferType type, const unsigned int size, const void* data, UsageType usageType);

        void setBufferSubData(BufferType type, const unsigned int offset, const unsigned int size, const void* data);


        /////////////////////////////////////////////////////////
        // Texture functions
        
        void setPixelStore(PixelStoreParam param, const int value);

        void generateTextures(const unsigned int amount, unsigned int* data);

        void setActiveTexUnit(TexUnit unit);

        void bindTexture(TextureType type, const int  texture);

        void setTextureImage1D(const int level, ImageFormat imageFormat, std::size_t width, ImageFormat pixelFormat, DataType dataType, const void* pixels);

        void setTextureImage2D(TextureType type, const int level, ImageFormat imageFormat, std::size_t width, std::size_t height, ImageFormat pixelFormat, DataType dataType, const void* pixels);

        void setTextureParameter(TextureType type, TextureParam param, const int value);




        /////////////////////////////////////////////////////////
        // Drawing functions




        /////////////////////////////////////////////////////////
        // Other



    private:

        Graphics();

        ~Graphics();



        int m_windowHandle;
        WindowSettings m_windowSettings;

    };
}