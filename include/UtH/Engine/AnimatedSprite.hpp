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

		AnimatedSprite(Texture* texture, const int frames, const umath::vector2 frameSize, 
			const float fps = 5.0f, const int firstFrame = 0, const bool reversed = false, const bool loop = true);
		AnimatedSprite(Texture* texture, const int frames, const int frameCountX, const int frameCountY, 
			const float fps = 5.0f, const int firstFrame = 0, const bool reversed = false, const bool loop = true);


		AnimatedSprite(const std::string filePath);

		void ChangeAnimation(int loopStartFrame, int loopFrames, int startFrame = 0, float fps = 5.0f);

		void Update(float dt);

	private:

		void genererateBuffer();

		int m_frames; // in the loop
		int m_firstFrame; // of the loop
		int m_curFrame;
		//int m_curRow;

		umath::rectangle m_frameSize;
		float m_fps;
		float delay;

		bool m_reversed;
		bool m_loop;

		int m_frameCountX;
		int m_frameCountY;

		umath::rectangle frame;
	};
}
#endif