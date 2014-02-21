#pragma once
#ifndef SPRITE_H_UTH
#define SPRITE_H_UTH

#include <string>

#include <UtH/Renderer/Texture.hpp>
#include <UtH/Math/Vector2.hpp>
#include <UtH/Engine/Component.hpp>

namespace uth
{
	class Sprite : public Component
	{
	public:
		Sprite();
		~Sprite();

		Sprite(Texture* texture);
		//Sprite(Texture* texture, umath::vector2 size);
		//Sprite(Texture* texture, int width, int height);

		Sprite(std::string filePath);
		//Sprite(std::string filePath, umath::vector2 size);
		//Sprite(std::string filePath, int width, int height);

		void Draw();
		void Update(float dt);

		void SetTexture(Texture* texture);

	private:

		Texture* texture;

		umath::vector2 m_size;

	};
}

#endif