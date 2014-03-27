#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Platform/Debug.hpp>


namespace uth
{
    RenderTarget::RenderTarget()
        : m_camera(nullptr),
          m_shader(nullptr),
          m_defaultCamera(),
          m_defaultShader()
    {
        
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
            bool compiled = m_defaultShader.LoadShader("vertexshader.vert", "fragmentshader.frag");
            assert(compiled);
            loaded = true;
        }

        if (m_shader)
            return *m_shader;

        return m_defaultShader;
    }
}