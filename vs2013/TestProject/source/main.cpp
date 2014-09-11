#include <UtH/uthEngine.hpp>

#define NEWSCENEFUNC
#include <Scenes.hpp>

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