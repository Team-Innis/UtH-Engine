#include "UtH/Engine/UtHEngine.h"

#include <UtH/Engine/SceneManager.hpp>

#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/Window.hpp> 
#include <UtH/Platform/Input.hpp>

using namespace uth;

int UtHEngine::MainLoop()
{
    uth::WindowSettings settings;
    settings.size = umath::vector2(1600, 900);
    settings.position = umath::vector2(8, 30);
	settings.contextVersionMajor = 2;
	settings.contextVersionMinor = 0;
    settings.fullScreen = false;

	CreateGameWindow(settings);

	while (m_running)
	{
		if(!Update())
			m_running = false;
		Draw();
		if(m_wndw->processMessages())
			m_running = false;
	}

    m_wndw->destroy();

	return 0;
}

UtHEngine::UtHEngine()
	: m_running(true)
{}

UtHEngine::~UtHEngine()
{}

bool UtHEngine::CreateGameWindow(uth::WindowSettings &settings)
{
	Window* window = new Window(settings);
	uthGraphics.setBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);
	SetWindow(window);
	return true;
}
bool UtHEngine::Update()
{
	return Update(m_timer.UpdateDeltaTime());
}
bool UtHEngine::Update(double dt)
{
	UTHInput.Update();
	return UtHSceneM.Update(dt);
}
void UtHEngine::Draw()
{
    m_wndw->clear(0.f, 0.f, 1.f);
	UtHSceneM.Draw();
    m_wndw->swapBuffers();
}

void UtHEngine::SetWindow(uth::Window * window)
{
	m_wndw = window;
	UTHInput.SetWindow(window->m_windowHandle);
}
