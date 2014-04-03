#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Graphics.hpp>


namespace uth
{
    RenderTarget::RenderTarget()
        : m_camera(nullptr),
          m_shader(nullptr),
          m_defaultCamera(),
          m_defaultShader(),
          m_viewport()
    {

    }


    bool RenderTarget::Bind()
    {
        updateUniforms();

        return bind();
    }

    void RenderTarget::Clear(const float r, const float g, const float b, const float a)
    {
        bind();

        uth::Graphics::Clear(r, g, b, a);
    }

    void RenderTarget::SetCamera(Camera* camera)
    {
        m_camera = camera;
    }

    Camera& RenderTarget::GetCamera()
    {
        static bool set = false;

        if (!set)
        {
            m_defaultCamera.SetSize(GetSize());
            m_defaultCamera.SetPosition(0, 0);
            set = true;
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
        static bool loaded = false;

        if (!loaded)
        {
            bool compiled = m_defaultShader.LoadShader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
            assert(compiled);
            loaded = true;
        }

        if (m_shader)
            return *m_shader;

        return m_defaultShader;
    }

    void RenderTarget::SetViewport(const umath::rectangle& rect)
    {
        m_viewport = rect;
    }

    const umath::rectangle& RenderTarget::GetViewport() const
    {
        return m_viewport;
    }

    void RenderTarget::updateUniforms()
    {
        if (m_shader)
        {
            m_shader->SetUniform("unifProjection", m_camera ? m_camera->GetProjectionTransform() : m_defaultCamera.GetProjectionTransform());

        }
        else
        {
            m_defaultShader.SetUniform("unifProjection", m_camera ? m_camera->GetProjectionTransform() : m_defaultCamera.GetProjectionTransform());

        }
    }
}