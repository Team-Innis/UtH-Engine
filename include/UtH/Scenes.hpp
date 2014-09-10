#pragma once
#ifndef SCENES_H_UTH
#define SCENES_H_UTH

#include <UtH/Engine/Scene.hpp>

#include <TestScene.hpp>

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
	DEFAULT = UTHDefaultScene,
	MENU,
	GAME,
	CREDITS,
	COUNT // Keep this last, it tells how many scenes there are
};

// Create function for a new scene, having a case for every user made scene
uth::Scene* NewSceneFunc(int SceneID)
{
	switch (SceneID)
	{
	case MENU:		return new /*Menu*/uth::TestScene();
	case GAME:		return new /*Game*/uth::TestScene();
	case CREDITS:	return new /*Credits*/uth::TestScene();
	default:		return nullptr;
	}
}

#endif //SCENES_H_UTH