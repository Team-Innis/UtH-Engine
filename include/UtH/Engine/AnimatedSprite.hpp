#pragma once
#ifndef ANIMATEDSPRITE_H_UTH
#define ANIMATEDSPRITE_H_UTH

#include <UtH/Engine/Sprite.hpp>
#include <UtH/Math/Rectangle.hpp>

namespace uth
{
	class AnimatedSprite : public Sprite
	{
	public:
		~AnimatedSprite();

		AnimatedSprite(Texture* texture, const unsigned int frames,
			const umath::vector2 frameSize,
			const float fps = 5.0f, const unsigned int firstFrame = 0,
			const bool reversed = false, const bool loop = true);
		AnimatedSprite(Texture* texture, const unsigned int frames,
			const unsigned int frameCountX, const unsigned int frameCountY,
			const float fps = 5.0f, const unsigned int firstFrame = 0,
			const bool reversed = false, const bool loop = true);


		//AnimatedSprite(const std::string filePath);

		void ChangeAnimation(int loopStartFrame, int loopFrames, 
			int startFrame = 0, float fps = 5.0f, bool loop = true, bool reversed = false);

		void Init();
		void Update(float dt);

	private:

		void genererateBuffer();

		unsigned int m_frames; // in the loop
		unsigned int m_firstFrame; // of the loop
		unsigned int m_curFrame;
		unsigned int m_frameCount;

		umath::rectangle m_frameSize;
		float m_fps;
		float m_delay;

		bool m_reversed;
		bool m_loop;
		bool testi;

		unsigned int m_frameCountX;
		unsigned int m_frameCountY;

		umath::rectangle frame;
	};
}
#endif