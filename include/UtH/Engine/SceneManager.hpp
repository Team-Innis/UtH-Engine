#ifndef SCENEMANAGER_H_UTH
#define SCENEMANAGER_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Platform/Singleton.hpp>
#include <functional>
#include <vector>

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

        typedef std::function<Scene*(const std::string&)> SceneCFunc;
        void AddSceneCreateFunc(SceneCFunc func);

        typedef std::function<Object*(const std::string&)> ObjectCFunc;
        void AddObjectCreateFunc(ObjectCFunc func);

        typedef std::function<Component*(const std::string&)> ComponentCFunc;
        void AddComponentCreateFunc(ComponentCFunc func);


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


        std::vector<SceneCFunc> m_sceneFuncs;

        friend class Object;
        std::vector<ObjectCFunc> m_objectFuncs;

        friend class GameObject;
        std::vector<ComponentCFunc> m_componentFuncs;


	};

}
//#include "UtH/Engine/Scenes.inl"
#endif
