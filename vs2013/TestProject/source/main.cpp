#include <UtH/Engine/UtHEngine.h>
#include <UtH/Engine/SceneManager.hpp>
#include <UtH/Platform/Debug.hpp>

#include <UtH/Engine/DefaultScene.hpp>

#include "TestScene.hpp"

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
	DEFAULT = UTHDefaultScene,
	MENU = 0,
	GAME = 1,
	CREDITS,
	COUNT // Keep this last, it tells how many scenes there are
};

// Create function for a new scene, having a case for every user made scene
void NewSceneFunc(int SceneID, uth::Scene* &CurScene)
{
	switch (SceneID)
	{
	case MENU:
		CurScene = new /*Menu*/uth::TestScene();
		break;
	case GAME:
		CurScene = new /*Game*/uth::TestScene();
		break;
	case CREDITS:
		CurScene = new /*Credits*/uth::TestScene();
		break;
	default:
		CurScene = new /*Menu*/uth::DefaultScene();
		break;
	}
}

int main()
{
	uthSceneM.registerNewSceneFunc(NewSceneFunc,COUNT);

	uthEngine.Init();

	while(uthEngine.Running())
	{
		uthEngine.Update();

		uthEngine.Draw();
	}

	return 0;
	//Hood.MainLoop(/*new StartScene*/);
	//uthSceneM.GoToScene(/*new GameScene*/1);
}