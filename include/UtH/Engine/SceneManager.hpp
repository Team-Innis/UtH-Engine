#ifndef SCENEMANAGER_H_UTH
#define SCENEMANAGER_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Platform/Singleton.hpp>

#define uthSceneM uth::SceneManager::getInstance()

namespace uth
{
	class SceneManager : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
	public:
		void GoToScene(int SceneNumber, bool disposeCurrent = true);

		void Update(float dt);
		void Draw();

		void DisposeScene(int SceneNumber);

		void registerNewSceneFunc(Scene* (*newSceneFunc)(int SceneID),int SceneCount);

        bool SaveCurrentScene(const std::string& saveName, const std::string& path);

        bool LoadSavedScene(const std::string& path);

	private:
		void endScene();
		void startScene();
		void m_switchScene();
		Scene* (*makeActiveScene)(int SceneID);

		Scene* curScene;

		int m_sceneID;
		int m_nextScene;
		int sceneCount;
		bool m_pendingSceneSwitch;


	};

}
//#include "UtH/Engine/Scenes.inl"
#endif
