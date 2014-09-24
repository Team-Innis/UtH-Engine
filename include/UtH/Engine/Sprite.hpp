#pragma once
#ifndef SPRITE_H_UTH
#define SPRITE_H_UTH

#include <UtH/Renderer/Texture.hpp>
#include <UtH/Engine/Component.hpp>
#include <UtH/Core/VertexBuffer.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <pmath/Vector.hpp>

namespace uth
{
    class RenderTarget;

	class Sprite : public Component
	{
	public:
		Sprite(Texture* texture, const std::string& name = "Sprite");
		//Sprite(Texture* texture, pmath::Vec2 size);
		//Sprite(Texture* texture, int width, int height);

		Sprite(const std::string& filePath, const std::string& name = "Sprite");
		//Sprite(std::string filePath, pmath::Vec2 size);
		//Sprite(std::string filePath, int width, int height);

		Sprite(const pmath::Vec4& fillColor, const pmath::Vec2& size,
			const std::string& name = "Sprite");

		virtual ~Sprite();

		virtual void Init();
		void Draw(RenderTarget& target) override;

		void SetTexture(Texture* texture);
		Texture* GetTexture() const;

		// Size of texture in pixels
		const pmath::Vec2& GetSize() const;

		// Just a simple multiplier for the texture color
		void SetColor(const pmath::Vec4& color);
		void SetColor(float r, float g, float b, float a);
		const pmath::Vec4& GetColor() const;

	protected:
		void defaults();

		virtual void generateBuffer(bool init = false);

		VertexBuffer m_vertexBuffer;

		Texture* m_texture;

		pmath::Vec2 m_size;

		pmath::Vec4 m_color;
	};
}

#endif