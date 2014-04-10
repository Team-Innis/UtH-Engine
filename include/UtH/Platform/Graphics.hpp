#pragma once
#ifndef GRAPHICS_H_UTH
#define GRAPHICS_H_UTH

#include <UtH/Platform/WindowSettings.hpp>
#include <UtH/Platform/Enums.hpp>
#include <UtH/Math/Math.hpp>

namespace uth
{

    class Graphics
    {
    public:
        
        /////////////////////////////////////////////////////////
        // Shader functions
        static const unsigned int CreateShaderProgram();

        // Creates the shader object, compiles the source and then attaches it to the program object.
        // Does not do the linking.
        static bool CreateShader(const ShaderType type, const int shaderProgram, const char* shaderCode);

        static bool LinkShaderProgram(const int shaderProgram);

        static void BindProgram(const int shaderProgram);

        static void UnbindProgram();

        static void DestroyShaderProgram(const int shaderProgram);

        static int GetUniformLocation(const int shaderProgram, const char* name);

        static int GetAttributeLocation(const int shaderProgram, const char* name);

        static void SetUniform(const int location, const int x);

        static void SetUniform(const int location, const float x);

        static void SetUniform(const int location, const float x, const float y);

        static void SetUniform(const int location, const float x, const float y, const float z);

        static void SetUniform(const int location, const float x, const float y, const float z, const float w);

        static void SetUniform(const int location, const umath::vector2& vector);

        static void SetUniform(const int location, const umath::vector3& vector);

        static void SetUniform(const int location, const umath::vector4& vector);

        static void SetUniform(const int location, const umath::matrix3& matrix);

        static void SetUniform(const int location, const umath::matrix4& matrix);

        static void EnableVertexAttribArray(const int location);

        static void DisableVertexAttribArray(const int location);

        static void SetVertexAttribPointer(const int location, const int size, DataType type, const int stride, const void* pointer);


        /////////////////////////////////////////////////////////
        // Buffer functions
        static void GenerateBuffers(const unsigned int amount, unsigned int* buffers);

        static void DeleteBuffers(const unsigned int amount, unsigned int* buffers);

        static void BindBuffer(BufferType type, const unsigned int buffer);

        static void SetBufferData(BufferType type, const unsigned int size, const void* data, UsageType usageType);

        static void SetBufferSubData(BufferType type, const unsigned int offset, const unsigned int size, const void* data);


        /////////////////////////////////////////////////////////
        // Framebuffer functions
        static void GenerateFrameBuffers(const unsigned int amount, unsigned int* buffers);

        static void DeleteFrameBuffers(const unsigned int amount, unsigned int* buffers);

        static void BindFrameBuffer(const unsigned int buffer);

        static void GenerateRenderBuffers(const unsigned int amount, unsigned int* buffers);

        static void DeleteRenderBuffers(const unsigned int amount, unsigned int* buffers);

        static void SetRenderBufferStorage(const unsigned int x, const unsigned int y);

        static void BindRenderBuffer(const unsigned int buffer);

        static void BindTextureToFrameBuffer(const unsigned int buffer, const unsigned int texture);

        static void BindRenderBufferToFrameBuffer(const unsigned int framebuffer, const unsigned int renderbuffer);


        /////////////////////////////////////////////////////////
        // Texture functions
        static void SetPixelStore(PixelStoreParam param, const int value);

        static void GenerateTextures(const unsigned int amount, unsigned int* data);

        static void DeleteTextures(const unsigned int amount, unsigned int* data);

        static void SetActiveTexUnit(TexUnit unit);

        static void BindTexture(TextureType type, const int texture);

        static void SetTextureImage1D(const int level, ImageFormat imageFormat, const unsigned int width, ImageFormat pixelFormat, DataType dataType, const void* pixels);

        static void SetTextureImage2D(TextureType type, const int level, ImageFormat imageFormat, const unsigned int width, const unsigned int height, ImageFormat pixelFormat, DataType dataType, const void* pixels);

        static void SetTextureParameter(TextureType type, TextureParam param, TextureFilter filter);


        /////////////////////////////////////////////////////////
        // Drawing functions
        static void DrawArrays(PrimitiveType type, const int first, const unsigned int count);

        static void DrawElements(PrimitiveType type, const unsigned int count, DataType dataType, const void* indices);

        static void SetPointSize(const float size);

        static void SetLineWidth(const float width);


        /////////////////////////////////////////////////////////
        // Other
        static void Clear(const float r = 0.0f, const float g = 0.0f, const float b = 0.0f, const float a = 1.0f);

        static void Flush();

        static void SetDepthFunction(const bool enable, DepthFunction func = LESS);

        static void SetBlendFunction(const bool enable, BlendFunction sfunc = ONE, BlendFunction dfunc = ZERO);

        static void SetFaceCulling(const bool enable, FaceCulling mode = BACK);

        static void SetViewport(const int x, const int y, const int width, const int height);



    private:

        Graphics();

        ~Graphics();

    };
}

#endif
