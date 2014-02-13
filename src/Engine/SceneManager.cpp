#include "UtH\Engine\Scene.hpp"
#include "UtH\Engine\Scene.hpp"//menu
#include "UtH\Engine\Scene.hpp"//game
#include "UtH\Engine\Scene.hpp"//credits

class SceneManager //:: singleton
{
	SceneManager()
	{
		setActiveScene(-1);
	}
	enum SceneName
	{
		DEFAULT = -1,
		MENU = 0,
		GAME = 1,
		CREDITS
	};

	void setActiveScene(int SceneNRO)
	{
		switch (SceneNRO)
		{
		case 0:
			curScene = new /*Game*/Scene();
			break;
		case 1:
			curScene = new /*Menu*/Scene();
			break;
		case 2:
			curScene = new /*Credits*/Scene();
			break;
		default:
			curScene = new /*Menu*/Scene();
			break;
		}
		sceneID = (SceneName)SceneNRO;
	}
	Scene* curScene;
	SceneName sceneID;
};