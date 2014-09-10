#include <UtH/Renderer/Camera.hpp>
#include <cmath>
#include <cassert>


namespace uth
{
    Camera::Camera()
        : m_zoom(1.f),
          m_projMatrix(),
          m_invProjMatrix(),
          m_transformNeedsUpdate(true),
          m_inverseTransformNeedsUpdate(true)
    {

    }

    Camera::Camera(const pmath::Vec2& position, const pmath::Vec2& size)
        : m_zoom(1.f),
        m_projMatrix(),
        m_invProjMatrix(),
        m_transformNeedsUpdate(true),
        m_inverseTransformNeedsUpdate(true)
    {
		transform.SetPosition(position);
    }

    Camera::~Camera()
    {

    }


    Camera& Camera::SetPosition(const pmath::Vec2& position)
    {
        transform.SetPosition(position);

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetPosition(const float x, const float y)
    {
        transform.SetPosition(x, y);

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetSize(const pmath::Vec2& size)
    {
        transform.size = size;

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetSize(const float x, const float y)
    {
        transform.size = pmath::Vec2(x, y);

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetRotation(const float degrees)
    {
        transform.SetRotation(degrees);

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetZoom(const float factor)
    {
		assert(m_zoom > 0.f);

        m_zoom = factor;

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::Scroll(const pmath::Vec2& offset)
    {
        transform.Move(offset);

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::Scroll(const float x, const float y)
    {
        transform.Move(x, y);

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::Rotate(const float offset)
    {
        transform.Rotate(offset);

        m_transformNeedsUpdate = true;
        m_inverseTransformNeedsUpdate = true;

        return *this;
    }

    const pmath::Vec2& Camera::GetPosition() const
    {
        return transform.GetPosition();
    }

    pmath::Vec2 Camera::GetSize() const
    {
        return pmath::Vec2(transform.size.x / m_zoom, transform.size.y / m_zoom);
    }

    float Camera::GetRotation() const
    {
        return transform.GetRotation();
    }

    const pmath::Mat4& Camera::GetProjectionTransform() const
    {
        if (m_transformNeedsUpdate)
        {
            const float rotation = transform.angle;
            const pmath::Vec2 position = transform.position;

            const float angle  = rotation * 3.141592654f / 180.f;
            const float cosine = static_cast<float>(std::cos(angle));
            const float sine   = static_cast<float>(std::sin(angle));
            const float tx     = -position.x * cosine - position.y * sine + position.x;
            const float ty     =  position.x * sine - position.y * cosine + position.y;

			const float sizeX = transform.size.x / m_zoom;
			const float sizeY = transform.size.y / m_zoom;

            const float a =  2.f / sizeX;
            const float b = -2.f / sizeY;
            const float c = -a * position.x;
            const float d = -b * position.y;

            m_projMatrix = pmath::Mat4( a * cosine, a * sine,   0.f, a * tx + c,
                                          -b * sine,   b * cosine, 0.f, b * ty + d,
                                           0.f,        0.f,        1.f, 0.f,
                                           0.f,        0.f,        0.f, 1.f);

            m_transformNeedsUpdate = false;
        }

        return m_projMatrix;
    }

    const pmath::Mat4& Camera::GetInverseProjectionTransform() const
    {
        if (m_inverseTransformNeedsUpdate)
        {
            m_invProjMatrix = GetProjectionTransform().inverse();
            m_inverseTransformNeedsUpdate = false;
        }

        return m_invProjMatrix;
    }

}