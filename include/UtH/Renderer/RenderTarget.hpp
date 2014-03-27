#pragma once
#ifndef RENDERTARGET_H_UTH
#define RENDERTARGET_H_UTH

#include <UtH/Renderer/Camera.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Platform/Uncopyable.hpp>
#include <UtH/Math/Vector2.hpp>


namespace uth
{

    class RenderTarget : private Uncopyable
    {
    public:

        void SetCamera(Camera* camera);

        Camera& GetCamera();

        void SetShader(Shader* shader);

        Shader& GetShader();


        virtual bool Bind() = 0;

        virtual umath::vector2 GetSize() const = 0;


    private:

        Camera* m_camera;
        Shader* m_shader;

        Camera m_defaultCamera;
        Shader m_defaultShader;


    protected:

        RenderTarget();

        virtual ~RenderTarget(){};

    };
}

#endif