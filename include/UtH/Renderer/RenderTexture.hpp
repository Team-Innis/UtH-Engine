#pragma once
#ifndef RENDERTEXTURE_H_UTH
#define RENDERTEXTURE_H_UTH

#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Resources/Texture.hpp>

namespace uth
{

    class RenderTexture : public RenderTarget
	{
		static std::unordered_set<RenderTexture*> RENDERTEXTURES;

		friend class ResourceManager;
    public:

        RenderTexture();

        ~RenderTexture();


        bool Initialize(const pmath::Vec2& size, const bool depthBuffer = false);

        pmath::Vec2 GetSize() const;

        Texture& GetTexture();

        void Update() const;

    private:

        bool bind();

        Texture m_texture;
        unsigned int m_frameBuffer,
                     m_depthBuffer;

    };
}

#endif