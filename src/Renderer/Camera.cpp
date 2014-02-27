#include <UtH\Renderer\Camera.hpp>
#include <cmath>


namespace uth
{
    Camera::Camera()
        : m_position(),
          m_size(),
          m_rotation(0.f),
          m_zoom(0.f),
          m_viewport(),
          m_transform(),
          m_transformNeedsUpdate(true)
    {

    }

    Camera::Camera(const umath::vector2& position, const umath::vector2& size)
        : m_position(position),
          m_size(size),
          m_rotation(0.f),
          m_zoom(0.f),
          m_viewport(),
          m_transform(),
          m_transformNeedsUpdate(true)
    {

    }

    Camera::~Camera()
    {

    }


    Camera& Camera::SetPosition(const umath::vector2& position)
    {
        m_position = position;

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetPosition(const float x, const float y)
    {
        m_position = umath::vector2(x, y);

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetSize(const umath::vector2& size)
    {
        m_size = size;

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetSize(const float x, const float y)
    {
        m_size = umath::vector2(x, y);

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetRotation(const float degrees)
    {
        m_rotation = degrees;

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetZoom(const float factor)
    {
        m_zoom = factor;

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::SetViewport(const umath::rectangle& rect)
    {
        m_viewport = rect;

        return *this;
    }

    Camera& Camera::Scroll(const umath::vector2& offset)
    {
        m_position += offset;

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::Scroll(const float x, const float y)
    {
        m_position += umath::vector2(x, y);

        m_transformNeedsUpdate = true;

        return *this;
    }

    Camera& Camera::Rotate(const float offset)
    {
        m_rotation += offset;

        m_transformNeedsUpdate = true;

        return *this;
    }

    const umath::vector2& Camera::GetPosition() const
    {
        return m_position;
    }

    const umath::vector2& Camera::GetSize() const
    {
        return m_size;
    }

    const float Camera::GetRotation() const
    {
        return m_rotation;
    }

    const umath::rectangle& Camera::GetViewport() const
    {
        return m_viewport;
    }

    const umath::matrix4& Camera::GetTransform() const
    {
        if (m_transformNeedsUpdate)
        {
            float angle  = m_rotation * 3.141592654f / 180.f;
            float cosine = static_cast<float>(std::cos(angle));
            float sine   = static_cast<float>(std::sin(angle));
            float tx     = -m_position.x * cosine - m_position.y * sine + m_position.x;
            float ty     =  m_position.x * sine - m_position.y * cosine + m_position.y;

            float a =  2.f / m_size.x;
            float b = -2.f / m_size.y;
            float c = -a * m_position.x;
            float d = -b * m_position.y;

            m_transform = umath::matrix4( a * cosine, a * sine, 0.f, a * tx + c,
                                         -b * sine, b * cosine, 0.f, b * ty + d,
                                          0.f, 0.f, 1.f, 0.f,
                                          0.f, 0.f, 0.f, 1.f);

            m_transformNeedsUpdate = false;
        }

        return m_transform;
    }
}