#include <UtH/Engine/UtHEngine.h>
#include <UtH/Engine/SceneManager.hpp>
#include <UtH/Platform/Debug.hpp>

#include <UtH/Engine/DefaultScene.hpp>

#include "TestScene.hpp"
//#include <UtH/Audio/Audio.hpp>

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

	//uth::SoundDevice* sd = new uth::SoundDevice();

	//uth::Audio* sound = new uth::Audio();
	//sound->Load("testi3.wav");
	//sound->Play();
	//sound->Loop(true);

	while(uthEngine.Running())
	{
		uthEngine.Update();

		uthEngine.Draw();
	}

	//delete sd;
	return 0;
	//Hood.MainLoop(/*new StartScene*/);
	//uthSceneM.GoToScene(/*new GameScene*/1);
}