#pragma once
#ifndef RENDERTARGET_H_UTH
#define RENDERTARGET_H_UTH

#include <UtH/Renderer/Camera.hpp>
#include <UtH/Resources/Shader.hpp>
#include <UtH/Platform/Uncopyable.hpp>
#include <pmath/Vector2.hpp>
#include <pmath/Rectangle.hpp>


namespace uth
{

    class RenderTarget : private Uncopyable
    {
    public:

        bool Bind();

        void Clear(const float r = 0.f, const float g = 0.f, const float b = 0.f, const float a = 1.f);

        void SetCamera(Camera* camera);

        Camera& GetCamera() const;

        void SetShader(Shader* shader);

        Shader& GetShader();

        void SetViewport(const pmath::Recti& rect);

        const pmath::Recti& GetViewport() const;

        virtual pmath::Vec2 GetSize() const = 0;

        pmath::Vec2 PixelToCoords(const pmath::Vec2& pixel) const;

        pmath::Vec2 CoordsToPixel(const pmath::Vec2& coords) const;


    private:

        virtual bool bind() = 0;

        void updateUniforms();

        mutable Camera* m_camera;
        Shader* m_shader;

        mutable Camera m_defaultCamera;

        pmath::Recti m_viewport;

        mutable bool m_set;

		static Shader* defaultShader;

		static bool shaderLoaded;

    protected:

        RenderTarget();

        virtual ~RenderTarget(){};

        const unsigned int m_uniqueID;

    };
}

#endif