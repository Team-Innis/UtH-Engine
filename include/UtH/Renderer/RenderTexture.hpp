#pragma once
#ifndef RENDERTEXTURE_H_UTH
#define RENDERTEXTURE_H_UTH

#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Renderer/Texture.hpp>

namespace uth
{

    class RenderTexture : public RenderTarget
	{
		//#ifdef UTH_SYSTEM_ANDROID
		static std::unordered_set<RenderTexture*> RENDERTEXTURES;
		//#endif
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