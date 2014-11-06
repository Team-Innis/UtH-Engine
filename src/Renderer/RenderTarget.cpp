#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <cassert>


namespace
{
    static const unsigned int getUniqueID()
    {
        static unsigned int id = 0;

        return ++id;
    }

}

namespace uth
{
	uth::Shader* RenderTarget::defaultShader;
	bool RenderTarget::shaderLoaded = false;

    RenderTarget::RenderTarget()
        : m_camera(nullptr),
          m_shader(nullptr),
          m_defaultCamera(),
          m_viewport(),
          m_set(false),
          m_uniqueID(getUniqueID())
    {

    }


    bool RenderTarget::Bind()
	{
        if (m_shader)
            m_shader->Use();
        else
			uthRS.LoadShader("Shaders/Default.vert", "Shaders/Default.frag")->Use();

        updateUniforms();

        static unsigned int lastID = 0;

        if (lastID != m_uniqueID)
        {
            lastID = m_uniqueID;
            return bind();
        }
        else
            return true;
    }

    void RenderTarget::Clear(const float r, const float g, const float b, const float a)
    {
        bind();

        uth::Graphics::Clear(r, g, b, a);
    }

    void RenderTarget::SetCamera(Camera* camera)
    {
        m_camera = camera;

        if (m_camera)
            m_camera->m_target = this;
    }

    Camera& RenderTarget::GetCamera() const
    {
        if (!m_set)
        {
            m_defaultCamera.SetSize(GetSize());
            m_defaultCamera.SetPosition(0, 0);
            m_set = true;
        }

        if (m_camera)
            return *m_camera;

        return m_defaultCamera;
    }

    void RenderTarget::SetShader(Shader* shader)
    {
        m_shader = shader;
    }

    Shader& RenderTarget::GetShader()
	{
        if (m_shader)
            return *m_shader;

		return *uthRS.LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
    }

    void RenderTarget::SetViewport(const pmath::Recti& rect)
    {
        m_viewport = rect;
    }

    const pmath::Recti& RenderTarget::GetViewport() const
    {
        return m_viewport;
    }

    pmath::Vec2 RenderTarget::PixelToCoords(const pmath::Vec2& pixel) const
    {
        pmath::Vec2 normalized;
        normalized.x = -1.f + 2.f * (pixel.x - m_viewport.getLeft()) / m_viewport.size.x;
        normalized.y = 1.f - 2.f * (pixel.y - m_viewport.getTop()) / m_viewport.size.y;

        return (GetCamera().GetInverseProjectionTransform() * normalized);
    }

    pmath::Vec2 RenderTarget::CoordsToPixel(const pmath::Vec2& point) const
    {
        pmath::Vec2 normalized = (GetCamera().GetProjectionTransform() * point);

        pmath::Vec2 pixel;
        pixel.x = (normalized.x + 1.f) / 2.f * m_viewport.size.x + m_viewport.getLeft();
        pixel.y = (-normalized.y + 1.f) / 2.f * m_viewport.size.y + m_viewport.getTop();

        return pixel;
    }

    void RenderTarget::updateUniforms()
    {
        if (m_shader)
        {
            m_shader->SetUniform("unifProjection", m_camera ? m_camera->GetProjectionTransform() : m_defaultCamera.GetProjectionTransform());
        }
        else
        {
			uthRS.LoadShader("Shaders/Default.vert", "Shaders/Default.frag")->SetUniform("unifProjection", m_camera ? m_camera->GetProjectionTransform() : m_defaultCamera.GetProjectionTransform());
        }
    }
}