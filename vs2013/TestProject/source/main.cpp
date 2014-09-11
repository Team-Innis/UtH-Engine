#include <UtH/uthEngine.hpp>
#include <UtH/Scenes.hpp>

#include "TestScene.hpp"

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