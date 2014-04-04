#include "UtH/Engine/UtHEngine.h"


#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/Input.hpp>

#include <iostream>

using namespace uth;

UTHEngine::UTHEngine()
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
	UTHInput.Update();
	uthSceneM.Update(deltaTime);
	
	if(m_wndw->processMessages())
	{
		m_running = false;
	}
}

void UTHEngine::Draw()
{
	m_wndw->Clear(0.f, 1.f, 0.f);
	uthSceneM.Draw();
    m_wndw->swapBuffers();
}

Window& UTHEngine::GetWindow()
{
    return *m_wndw;
}

bool UTHEngine::initialize()
{
	m_wndw = new Window(m_wsettings);
	uth::Graphics::SetBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);
	UTHInput.SetWindow(m_wndw->m_windowHandle);
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