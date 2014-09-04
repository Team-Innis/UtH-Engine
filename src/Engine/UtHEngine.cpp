#include "UtH/Engine/UtHEngine.h"


#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/Input.hpp>

using namespace uth;

UTHEngine::UTHEngine()
    : m_running(false)
{ }

bool UTHEngine::Init()
{
    m_wsettings.size = umath::vector2(1280, 720);
    m_wsettings.position = umath::vector2(100, 100);
	m_wsettings.contextVersionMajor = 3;
	m_wsettings.contextVersionMinor = 3;
    m_wsettings.fullScreen = false;
	m_wsettings.useVsync = true;

	return initialize();
}

bool UTHEngine::Init(const uth::WindowSettings &wsettings)
{
	m_wsettings = wsettings;
	return initialize();
}

void UTHEngine::Update()
{
	const float deltaTime = static_cast<float>(m_timer.DeltaTime());
	uthInput.Update(deltaTime);
	
	if(!uthSceneM.Update(deltaTime) || m_wndw->processMessages())
	{
		m_running = false;
	}
}

void UTHEngine::Draw()
{
	m_wndw->Clear(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
	uthSceneM.Draw();
    m_wndw->swapBuffers();
}

void UTHEngine::SetClearColor(const umath::vector4& color)
{
    m_clearColor = color;
}

void UTHEngine::SetClearColor(float r, float g, float b, float a)
{
    SetClearColor(umath::vector4(r, g, b, a));
}

Window& UTHEngine::GetWindow()
{
    return *m_wndw;
}

bool UTHEngine::initialize()
{
	m_wndw = new Window(m_wsettings);
	uth::Graphics::SetBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);
	uthInput.SetWindow(m_wndw->m_windowHandle);
	m_running = true;

	return true;
}

const Timer UTHEngine::timer() const
{
	return m_timer;
}

const umath::vector2 UTHEngine::GetWindowResolution() const
{
	return m_wsettings.size;
}

const bool UTHEngine::Running() const
{
	return m_running;
}

void UTHEngine::SetWindow(void* handle)
{
	m_wndw = (Window*)handle;
}