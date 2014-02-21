#include "UtH\Engine\UtHEngine.h"

#include <UtH\Engine\SceneManager.hpp>

using namespace uth;

int UtHEngine::AutoMainLoop()
{
	while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
	{
		Update();
		Draw();
	}

	return 0;
}

UtHEngine::UtHEngine()
{}

UtHEngine::~UtHEngine()
{}

bool UtHEngine::CreateGameWindow()
{
	return true;
}
bool UtHEngine::Update()
{
	UtHSceneM.Update(0.1);
	//window->throwExeption
	return true;
}
void UtHEngine::Draw()
{
	UtHSceneM.Draw();
	//window->clear();
	//ObjectManager->Draw();
	//SwapBuffers();
}
