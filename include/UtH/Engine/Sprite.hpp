#pragma once
#ifndef SPRITE_H_UTH
#define SPRITE_H_UTH

#include <UtH/Renderer/Texture.hpp>
#include <UtH/Math/Vector2.hpp>
#include <UtH/Engine/Component.hpp>
#include <UtH/Core/VertexBuffer.hpp>

namespace uth
{
	class Sprite : public Component
	{
	public:
		Sprite(Texture* texture, const std::string name = "Sprite");
		//Sprite(Texture* texture, umath::vector2 size);
		//Sprite(Texture* texture, int width, int height);

		Sprite(const std::string filePath, const std::string name = "Sprite");
		//Sprite(std::string filePath, umath::vector2 size);
		//Sprite(std::string filePath, int width, int height);

		~Sprite();

		void Draw(Shader* shader);
		void Update(float dt);

		void SetTexture(Texture* texture);
		// Size of texture in pixels
		const umath::vector2 GetSize() const;

	private:
		void generetateBuffer();

		VertexBuffer* vertexBuffer;

		Texture* texture;

		umath::vector2 m_size;
	};
}

#endif