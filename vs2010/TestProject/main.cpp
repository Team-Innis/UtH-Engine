#include <UtH/Engine/UtHEngine.h>
#include <UtH/Engine/SceneManager.hpp>

#include <UtH/Engine/DefaultScene.hpp>
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
		CurScene = new /*Menu*/uth::DefaultScene();
		break;
	case GAME:
		CurScene = new /*Game*/uth::DefaultScene();
		break;
	case CREDITS:
		CurScene = new /*Credits*/uth::DefaultScene();
		break;
	default:
		CurScene = new /*Menu*/uth::DefaultScene();
		break;
	}
}

int main()
{
	UtHSceneM.registerNewSceneFunc(NewSceneFunc,COUNT);

	uthEngine.Init();

	while(uthEngine.Running())
	{
		uthEngine.Update(uthEngine.Timer().GetMemTime());

		uthEngine.Draw();
	}

	return 0;
	//Hood.MainLoop(/*new StartScene*/);
	//UtHSceneM.GoToScene(/*new GameScene*/1);
}