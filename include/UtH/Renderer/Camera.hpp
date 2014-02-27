#pragma once
#ifndef CAMERA_H_UTH
#define CAMERA_H_UTH

#include <UtH\Math\Vector2.hpp>
#include <UtH\Math\Matrix4.hpp>
#include <UtH\Math\Rectangle.hpp>
#include <UtH\Engine\GameObject.hpp>


namespace uth
{
    class Camera : public GameObject
    {
    public:

        Camera();

        Camera(const umath::vector2& position, const umath::vector2& size);

        ~Camera();


        /// Position is the CENTER position of the camera.
        Camera& SetPosition(const umath::vector2& position);

        Camera& SetPosition(const float x, const float y);

        Camera& SetSize(const umath::vector2& size);

        Camera& SetSize(const float x, const float y);

        Camera& SetRotation(const float degrees);

        Camera& SetZoom(const float factor);

        Camera& SetViewport(const umath::rectangle& rect);

        Camera& Scroll(const umath::vector2& offset);

        Camera& Scroll(const float x, const float y);

        Camera& Rotate(const float offset);

        const umath::vector2& GetPosition() const;

        const umath::vector2& GetSize() const;

        float GetRotation() const;

        const umath::rectangle& GetViewport() const;

        const umath::matrix4& GetViewTransform() const;



    private:

        umath::vector2 m_size;
        float m_zoom;
        umath::rectangle m_viewport;
        mutable umath::matrix4 m_viewMatrix;
        mutable bool m_transformNeedsUpdate;

    };
}

#endif