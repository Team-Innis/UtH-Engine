#include <UtH/Renderer/RenderTexture.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Graphics.hpp>


namespace uth
{

    RenderTexture::RenderTexture()
        : m_texture(),
          m_frameBuffer(0),
          m_depthBuffer(0)
    {

    }

    RenderTexture::~RenderTexture()
    {
        uth::Graphics::BindFrameBuffer(0);

        if (m_frameBuffer)
            uth::Graphics::DeleteFrameBuffers(1, &m_frameBuffer);
        if (m_depthBuffer)
            uth::Graphics::DeleteRenderBuffers(1, &m_depthBuffer);
    }


    bool RenderTexture::Initialize(const umath::vector2& size, const bool depthBuffer)
    {
        if (!m_texture.Create(size, false, false))
        {
            WriteError("Failed to create rendertexture texture");
            return false;
        }

        uth::Graphics::GenerateFrameBuffers(1, &m_frameBuffer);
        
        if (!m_frameBuffer)
        {
            WriteError("Failed to create rendertexture framebuffer");
            return false;
        }

        uth::Graphics::BindFrameBuffer(m_frameBuffer);

        if (depthBuffer)
        {
            uth::Graphics::GenerateRenderBuffers(1, &m_depthBuffer);

            if (!m_depthBuffer)
            {
                WriteError("Failed to create rendertexture depth buffer");
                uth::Graphics::DeleteFrameBuffers(1, &m_frameBuffer);
                m_frameBuffer = 0;
                return false;
            }

            uth::Graphics::BindRenderBuffer(m_depthBuffer);
            uth::Graphics::SetRenderBufferStorage(
				static_cast<unsigned int>(size.x), 
				static_cast<unsigned int>(size.y));
            uth::Graphics::BindRenderBufferToFrameBuffer(m_frameBuffer, m_depthBuffer);
        }

        uth::Graphics::BindTextureToFrameBuffer(m_frameBuffer, m_texture.GetTextureID());

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            uth::Graphics::DeleteFrameBuffers(1, &m_frameBuffer);
            uth::Graphics::DeleteRenderBuffers(1, &m_depthBuffer);
            WriteError("Failed to bind texture to rendertexture");
            return false;
        }

        return true;
    }

    umath::vector2 RenderTexture::GetSize() const
    {
        return m_texture.GetSize();
    }

    Texture& RenderTexture::GetTexture()
    {
        return m_texture;
    }

    void RenderTexture::Update() const
    {
        uth::Graphics::Flush();
    }

    bool RenderTexture::bind()
    {
        if (m_frameBuffer)
        {
            uth::Graphics::BindFrameBuffer(m_frameBuffer);
            return true;
        }

        return false;
    }
}