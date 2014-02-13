#include "UtH/Engine/SceneManager.hpp"
#ifndef SCENEMANAGER_H_UTH
#define SCENEMANAGER_H_UTH

uth::Scene* curScene;

enum SceneName
{
	DEFAULT = -1,
	MENU = 0,
	GAME = 1,
	CREDITS,
	COUNT // Keep this last, it tells how many scenes there are
};

bool setActiveScene(int SceneID)
{
		
	switch (SceneID)
	{
	case MENU:
		curScene = new /*Menu*/Scene();
		break;
	case GAME:
		curScene = new /*Game*/Scene();
		break;
	case CREDITS:
		curScene = new /*Credits*/Scene();
		break;
	default:
		curScene = new /*Menu*/Scene();
		break;
	}
}

#endif