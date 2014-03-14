#ifndef SCENEMANAGER_HPP_UTH
#define SCENEMANAGER_HPP_UTH

#include "UtH/Engine/Scene.hpp"
#include <UtH/Platform/Singleton.hpp>

#define UtHSceneM uth::SceneManager::getInstance()
#define UTHDefaultScene -1

namespace uth
{
	class SceneManager : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
	public:
		void GoToScene(int SceneNumber);
		void GoToScene(Scene* newScene);

		bool Update(double dt);
		bool Draw();


		void registerNewSceneFunc(void (*newSceneFunc)(int SceneID, Scene* &CurScene),int SceneCount);
		

	private:
		void endScene();
		void startScene();
		void m_switchScene();
		void (*makeActiveScene)(int SceneID, Scene* &CurScene);

		Scene* curScene;

		int m_sceneID;
		int m_nextScene;
		int sceneCount;
		bool m_pendingSceneSwitch;


	};

}
//#include "UtH/Engine/Scenes.inl"
#endif
