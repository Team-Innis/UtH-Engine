#include "UtH/Engine/UtHEngine.h"

#include <UtH/Engine/SceneManager.hpp>

#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/Window.hpp> 

using namespace uth;

int UtHEngine::AutoMainLoop()
{
    uth::WindowSettings settings;
    settings.size = umath::vector2(1600, 900);
    settings.position = umath::vector2(8, 30);
	settings.contextVersionMajor = 3;
	settings.contextVersionMinor = 1;
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
	m_wndw = new Window(settings);
	uthGraphics.setBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);
	return true;
}
bool UtHEngine::Update()
{
	return Update(m_timer.UpdateDeltaTime());
}
bool UtHEngine::Update(double dt)
{
	return UtHSceneM.Update(dt);
}
void UtHEngine::Draw()
{
    m_wndw->clear(0.f, 0.f, 1.f);
	UtHSceneM.Draw();
    m_wndw->swapBuffers();
}
