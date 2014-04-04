#pragma once
#ifndef SPRITE_H_UTH
#define SPRITE_H_UTH

#include <UtH/Renderer/Texture.hpp>
#include <UtH/Math/Vector.hpp>
#include <UtH/Engine/Component.hpp>
#include <UtH/Core/VertexBuffer.hpp>
#include <UtH/Resources/ResourceManager.h>

namespace uth
{
    class RenderTarget;

	class Sprite : public Component
	{
	public:
		Sprite(Texture* texture, const std::string& name = "Sprite");
		//Sprite(Texture* texture, umath::vector2 size);
		//Sprite(Texture* texture, int width, int height);

		Sprite(const std::string& filePath, const std::string& name = "Sprite");
		//Sprite(std::string filePath, umath::vector2 size);
		//Sprite(std::string filePath, int width, int height);

		Sprite(const umath::vector4& fillColor, const umath::vector2& size,
			const std::string& name = "Sprite");

		virtual ~Sprite();

		virtual void Init();
		void Draw(RenderTarget& target);

		void SetTexture(Texture* texture);
		Texture* GetTexture() const;

		// Size of texture in pixels
		const umath::vector2& GetSize() const;

		// Just a simple multiplier for the texture color
		void SetColor(const umath::vector4& color);
		void SetColor(float r, float g, float b, float a);
		const umath::vector4& GetColor() const;

	protected:
		void defaults();

		virtual void generateBuffer();

		VertexBuffer m_vertexBuffer;

		Texture* m_texture;

		umath::vector2 m_size;

		umath::vector4 m_color;
	};
}

#endif