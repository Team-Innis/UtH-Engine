
inline enum uth::SceneManager::SceneName
{
	DEFAULT = -1,
	MENU = 0,
	GAME = 1,
	CREDITS,
	COUNT // Keep this last, it tells how many scenes there are
};

inline void uth::SceneManager::makeActiveScene(SceneName SceneID)
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