#pragma once
#ifndef RENDERTARGET_H_UTH
#define RENDERTARGET_H_UTH

#include <UtH/Renderer/Camera.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Platform/Uncopyable.hpp>
#include <UtH/Math/Vector2.hpp>
#include <UtH/Math/Rectangle.hpp>


namespace uth
{

    class RenderTarget : private Uncopyable
    {
    public:

        void SetCamera(Camera* camera);

        Camera& GetCamera();

        void SetShader(Shader* shader);

        Shader& GetShader();

        void SetViewport(const umath::rectangle& rect);

        const umath::rectangle& GetViewport() const;

        bool Bind();

        virtual umath::vector2 GetSize() const = 0;

        void Clear(const float r = 0.f, const float g = 0.f, const float b = 0.f, const float a = 1.f);


    private:

        virtual bool bind() = 0;

        void updateUniforms();

        Camera* m_camera;
        Shader* m_shader;

        Camera m_defaultCamera;
        Shader m_defaultShader;

        umath::rectangle m_viewport;


        bool m_loaded, m_set;


    protected:

        RenderTarget();

        virtual ~RenderTarget(){};

        const unsigned int m_uniqueID;

    };
}

#endif