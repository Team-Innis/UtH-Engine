#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <cassert>

using namespace uth;

AnimatedSprite::AnimatedSprite(Texture* texture, const unsigned int frames,
	const pmath::Vec2& frameSize,
	const float fps, const unsigned int firstFrame,
	const bool reversed, const bool loop)
	: Sprite(texture, "AnimatedSprite"),
		m_frames(frames),
		m_firstFrame(firstFrame),
		m_curFrame(firstFrame),
		m_fps(fps),
		m_delay(0.0f),
		m_reversed(reversed),
		m_loop(loop)
{
	const pmath::Vec2 texSize = texture->GetSize();
#ifndef NDEBUG
	if(int(texSize.x) % int(frameSize.x) != 0 || int(texSize.y) % int(frameSize.y) != 0)
	{
		WriteError("Bad frame size! texture(%f, %f) frame(%f, %f)",
			texSize.x, texSize.y, frameSize.x, frameSize.y);
		assert(false);
	}
#endif
	m_frameCountX = static_cast<unsigned int>(texSize.x / frameSize.x);
	m_frameCountY = static_cast<unsigned int>(texSize.y / frameSize.y);
	AnimatedSprite(texture, frames, m_frameCountX, m_frameCountY, fps, firstFrame, reversed, loop);
}

AnimatedSprite::AnimatedSprite(Texture* texture, const unsigned int frames,
	const unsigned int frameCountX, const unsigned int frameCountY,
	const float fps, const unsigned int firstFrame,
	const bool reversed, const bool loop)
	: Sprite(texture, "AnimatedSprite"),
		m_frames(frames),
		m_firstFrame(firstFrame),
		m_curFrame(firstFrame),
		m_fps(fps),
		m_delay(0.0f),
		m_reversed(reversed),
		m_loop(loop),
		m_frameCountX(frameCountX),
        m_frameCountY(frameCountY)
{
	const unsigned int texSizeX = static_cast<const unsigned int>(texture->GetSize().x);
	const unsigned int texSizeY = static_cast<const unsigned int>(texture->GetSize().y);

#ifndef NDEBUG
	if(texSizeX % frameCountX != 0 || texSizeY % frameCountY != 0)
	{
		WriteError("Bad texture size! (%d, %d)", texSizeX, texSizeY);
		assert(false);
	}
	if(frames > frameCountX * frameCountY)
	{
		WriteError("Too many frames! (maximum frame capacity: %d)", frameCountX * frameCountY);
		assert(false);
	}
#endif
	// frame size in pixels
	m_frameSize.position.x = static_cast<const float>(texSizeX / frameCountX);
	m_frameSize.position.y = static_cast<const float>(texSizeY / frameCountY);
	// frame size in texcoord float
	m_frameSize.size.x = 1.0f / frameCountX;
	m_frameSize.size.y = 1.0f / frameCountY;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::ChangeAnimation(int loopStartFrame, int loopFrames,
	int startFrame, float fps, bool loop, bool reversed)
{

#ifndef NDEBUG
	if(loopFrames == 0)
	{
		WriteError("0 frame animation? (frame count = 0)");
		assert(false);
	}
#endif
	if(startFrame < loopStartFrame)
		m_curFrame = loopStartFrame;
	else
		m_curFrame = startFrame;

	m_frames = loopFrames;
	m_firstFrame = loopStartFrame;
	m_fps = fps;
	m_loop = loop;
	m_frameCount = 0;
	m_reversed = reversed;
	genererateBuffer();
}

void AnimatedSprite::Init()
{
	ChangeAnimation(m_firstFrame,m_frames,m_firstFrame, m_fps, m_loop, m_reversed);

	const pmath::Vec2 size = pmath::Vec2(m_frameSize.position.x, m_frameSize.position.y);
	parent->transform.SetSize(size);

	loopEnd = false;
}

void AnimatedSprite::Update(float dt)
{
    if (m_frames < 2 || m_fps == 0)
        return;

	m_delay += dt;

	if (!m_loop)
	{
		if(m_frames == m_frameCount + 1)
			loopEnd = true;
	}

	if(m_delay > 1.0f / m_fps && !loopEnd)
	{
		m_delay = 0.0f;
		m_frameCount++;

		if(!m_reversed)
		{
			m_curFrame++;
			if (m_curFrame - m_firstFrame >= m_frames)
			{
				m_curFrame -= m_frames;
			}
		}
		else
		{
			m_curFrame--;
			if(m_curFrame < m_firstFrame)
			{
				m_curFrame = m_firstFrame + m_frames;
			}
		}
		genererateBuffer();
	}
}

void AnimatedSprite::genererateBuffer()
{
	const int X = m_curFrame % m_frameCountX;
	const int Y = m_curFrame/m_frameCountX;

	frame.position.x = X * m_frameSize.size.x;
	frame.size.x = m_frameSize.size.x;
	frame.position.y = 1.0f - Y * m_frameSize.size.y;
	frame.size.y = -m_frameSize.size.y;

	m_vertexBuffer.clear();

	m_vertexBuffer.addVertex(Vertex(
		pmath::Vec3(-0.5f, -0.5f, 0),
		pmath::Vec2(frame.getLeft(), frame.getTop()),
		m_color));
	m_vertexBuffer.addVertex(Vertex(
		pmath::Vec3(0.5f, -0.5f, 0),
		pmath::Vec2(frame.getRight(), frame.getTop()),
		m_color));
	m_vertexBuffer.addVertex(Vertex(
		pmath::Vec3(-0.5f, 0.5f, 0),
		pmath::Vec2(frame.getLeft(), frame.getBottom()),
		m_color));
	m_vertexBuffer.addVertex(Vertex(
		pmath::Vec3(0.5f, 0.5f, 0),
		pmath::Vec2(frame.getRight(), frame.getBottom()),
		m_color));


	m_vertexBuffer.addIndex(0);
	m_vertexBuffer.addIndex(1);
	m_vertexBuffer.addIndex(2);
	m_vertexBuffer.addIndex(1);
	m_vertexBuffer.addIndex(3);
	m_vertexBuffer.addIndex(2);
}