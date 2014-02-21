#include "UtH/Engine/Scene.hpp"
#ifndef SCENEMANAGER_HPP_UTH
#define SCENEMANAGER_HPP_UTH

#include <UtH/Platform/Singleton.hpp>

#define UtHSceneM uth::SceneManager::getInstance()

namespace uth
{

	class SceneManager : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
	public:
		//inline enum SceneName;
		enum SceneName
		{
			DEFAULT = -1,
			MENU = 0,
			GAME = 1,
			CREDITS,
			COUNT // Keep this last, it tells how many scenes there are
		};
		//inline bool setActiveScene(int SceneID);
		void SwapToScene(SceneName SceneID);
		void SwapToScene(int SceneNumber);

		bool Update(double dt);
		bool Draw();


		void setNewSceneFunc(Scene* (*makeActiveScene)(SceneName SceneID, Scene* CurScene));
		

	//private:
		void endScene();
		void startScene();
		void m_switchScene();
		Scene* (*makeActiveScene)(SceneName SceneID, Scene* CurScene);
		//void defaultNewSceneFunc(SceneName SceneID, Scene* CurScene);

		Scene* curScene;
		SceneName m_sceneID;
		SceneName m_nextScene;
		bool m_pendingSceneSwitch;


	};

}
//#include "UtH/Engine/Scenes.inl"
#endif
