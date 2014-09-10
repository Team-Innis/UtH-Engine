#include <UtH/uthEngine.hpp>
#include <UtH/Scenes.hpp>

//#include <UtH/Audio/Audio.hpp>

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