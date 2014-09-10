#pragma once
#ifndef CAMERA_H_UTH
#define CAMERA_H_UTH


#include <pmath/Vector2.hpp>
#include <pmath/Matrix4.hpp>
#include <pmath/Rectangle.hpp>
#include <UtH/Engine/GameObject.hpp>


namespace uth
{
    class Camera : public GameObject
    {
    public:

        Camera();

        Camera(const pmath::Vec2& position, const pmath::Vec2& size);

        ~Camera();


        /// Position is the CENTER position of the camera.
        Camera& SetPosition(const pmath::Vec2& position);

        Camera& SetPosition(const float x, const float y);

        Camera& SetSize(const pmath::Vec2& size);

        Camera& SetSize(const float x, const float y);

        Camera& SetRotation(const float degrees);

        Camera& SetZoom(const float factor);

        Camera& Scroll(const pmath::Vec2& offset);

        Camera& Scroll(const float x, const float y);

        Camera& Rotate(const float offset);

        const pmath::Vec2& GetPosition() const;

        pmath::Vec2 GetSize() const;

        float GetRotation() const;

        const pmath::Mat4& GetProjectionTransform() const;

        const pmath::Mat4& GetInverseProjectionTransform() const;


    private:

        float m_zoom;
        mutable pmath::Mat4 m_projMatrix,
                            m_invProjMatrix;
        mutable bool m_transformNeedsUpdate,
                     m_inverseTransformNeedsUpdate;
    };
}

#endif
