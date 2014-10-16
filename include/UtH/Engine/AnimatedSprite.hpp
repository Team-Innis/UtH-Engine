#pragma once
#ifndef ANIMATEDSPRITE_H_UTH
#define ANIMATEDSPRITE_H_UTH

#include <UtH/Engine/Sprite.hpp>
#include <pmath/Rectangle.hpp>

namespace uth
{
	class AnimatedSprite : public Sprite
	{
	public:
		~AnimatedSprite();

		AnimatedSprite(Texture* texture, const unsigned int frames,
			const pmath::Vec2& frameSize,
			const float fps = 5.0f, const unsigned int firstFrame = 0,
			const bool reversed = false, const bool loop = true);
		AnimatedSprite(Texture* texture, const unsigned int frames,
			const unsigned int frameCountX, const unsigned int frameCountY,
			const float fps = 5.0f, const unsigned int firstFrame = 0,
			const bool reversed = false, const bool loop = true);


		//AnimatedSprite(const std::string filePath);

		void ChangeAnimation(int loopStartFrame, int loopFrames,
			int startFrame = 0, float fps = 5.0f, bool loop = true, bool reversed = false);
		void ChangeSpeed(float fps);

		void Init();
		void Update(float dt);

	private:

		void generateBuffer(bool init = false);

		unsigned int m_frames; // in the loop
		int m_firstFrame; // of the loop
		int m_curFrame;
		unsigned int m_frameCount;

		// frame size in pixels
		pmath::Vec2 m_sizePx;
		// frame size in texture coordinates
		pmath::Vec2 m_sizeTc;

		float m_fps;
		float m_delay;

		bool m_reversed;
		bool m_loop;
		bool loopEnd;

		unsigned int m_frameCountX;
		unsigned int m_frameCountY;
	};
}
#endif