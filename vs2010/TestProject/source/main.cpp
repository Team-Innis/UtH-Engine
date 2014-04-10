#include <UtH/Engine/UtHEngine.h>
#include <UtH/Engine/SceneManager.hpp>
#include <UtH/Platform/Debug.hpp>

#include <UtH/Engine/DefaultScene.hpp>

#include "TestScene.hpp"
#include <UtH/Audio/Audio.h>
#include <UtH/Audio/SoundManager.h>

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

	//uth::SoundManager* sm = new uth::SoundManager();

	//uth::Audio* sound = new uth::Audio();
	//sound->Load("testi3.wav");
	//sound->Play();
	//sound->Loop(true);

	while(uthEngine.Running())
	{
		uthEngine.Update();

		uthEngine.Draw();
	}

	//delete sm;
	return 0;
	//Hood.MainLoop(/*new StartScene*/);
	//uthSceneM.GoToScene(/*new GameScene*/1);
}