#pragma once

#include <UtH/Math/Vector2.hpp>
#include <UtH/Math/Matrix4.hpp>
#include <UtH/Math/Rectangle.hpp>


namespace uth
{
    class Camera
    {
    public:

        Camera();

        Camera(const umath::vector2& position, const umath::vector2& size);

        ~Camera();


        /// Position is the CENTER position of the camera.
        Camera& setPosition(const umath::vector2& position);

        Camera& setPosition(const float x, const float y);

        Camera& setSize(const umath::vector2& size);

        Camera& setSize(const float x, const float y);

        Camera& setRotation(const float degrees);

        Camera& setZoom(const float factor);

        Camera& setViewport(const umath::rectangle& rect);

        Camera& scroll(const umath::vector2& offset);

        Camera& scroll(const float x, const float y);

        Camera& rotate(const float offset);

        const umath::vector2& getPosition() const;

        const umath::vector2& getSize() const;

        const float getRotation() const;

        const umath::rectangle& getViewport() const;

        const umath::matrix4& getTransform() const;



    private:

        umath::vector2 m_position;
        umath::vector2 m_size;
        float m_rotation;
        float m_zoom;
        umath::rectangle m_viewport;
        mutable umath::matrix4 m_transform;
        mutable bool m_transformNeedsUpdate;

    };
}