#pragma once
#ifndef GRAPHICS_H_UTH
#define GRAPHICS_H_UTH

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
        // Shader functions
        int createShaderProgram();

        // Creates the shader object, compiles the source and then attaches it to the program object.
        // Does not do the linking.
        bool createShader(const ShaderType type, const int shaderProgram, const char* shaderCode);

        bool linkShaderProgram(const int shaderProgram);

        void bindProgram(const int shaderProgram);

        void unbindProgram();

        void destroyShaderProgram(const int shaderProgram);

        int getUniformLocation(const int shaderProgram, const char* name);

        int getAttributeLocation(const int shaderProgram, const char* name);

        void setUniform(const int location, const int x);

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

        void setVertexAttribPointer(const int location, const int size, DataType type, const int stride, const void* pointer);


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

        void deleteTextures(const unsigned int amount, unsigned int* data);

        void setActiveTexUnit(TexUnit unit);

        void bindTexture(TextureType type, const int texture);

        void setTextureImage1D(const int level, ImageFormat imageFormat, const unsigned int width, ImageFormat pixelFormat, DataType dataType, const void* pixels);

        void setTextureImage2D(TextureType type, const int level, ImageFormat imageFormat, const unsigned int width, const unsigned int height, ImageFormat pixelFormat, DataType dataType, const void* pixels);

        void setTextureParameter(TextureType type, TextureParam param, TextureFilter filter);


        /////////////////////////////////////////////////////////
        // Drawing functions
        void drawArrays(PrimitiveType type, const int first, const unsigned int count);

        void drawElements(PrimitiveType type, const unsigned int count, DataType dataType, const void* indices);

        void setPointSize(const float size);

        void setLineWidth(const float width);


        /////////////////////////////////////////////////////////
        // Other
        void flush();

        void setDepthFunction(const bool enable, DepthFunction func = LESS);

        void setBlendFunction(const bool enable, BlendFunction sfunc = ONE, BlendFunction dfunc = ZERO);

        void setFaceCulling(const bool enable, FaceCulling mode = BACK);



    private:

        Graphics();

        ~Graphics();

    };
}

#endif
