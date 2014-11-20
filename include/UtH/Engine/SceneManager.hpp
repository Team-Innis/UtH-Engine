#ifndef SCENEMANAGER_H_UTH
#define SCENEMANAGER_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/Saveable.hpp>
#include <functional>
#include <unordered_map>
#include <type_traits>
#include <rapidjson/document.h>

#define uthSceneM uth::SceneManager::GetInstance()

namespace uth
{
	class SceneManager
	{
		SceneManager();
		~SceneManager();
	public:

        static SceneManager& GetInstance();

		void GoToScene(int SceneNumber, bool disposeCurrent = true);

		void Update(float dt);
		void Draw();

		void DisposeScene(int SceneNumber);

		void registerNewSceneFunc(Scene* (*newSceneFunc)(int SceneID),int SceneCount);

        bool SaveCurrentScene(const std::string& saveName);

        bool LoadCurrentScene(const std::string& saveName);


        typedef std::function<Saveable*(const rapidjson::Value& val)> ObjectCFunc;

        template<typename T>
        void RegisterSaveable()
        {
            static_assert(std::is_base_of<Saveable, T>::value, "Tried to register an object that doesn't derive from uth::Saveable");
            static_assert(!std::is_reference<T>::value && !std::is_pointer<T>::value, "Tried to register an object as pointer or reference. Must be full definition.");

            m_saveableFuncs.emplace(typeid(T).raw_name(), [](const rapidjson::Value&) -> Saveable*
            {
                return new T();
            });
        }

        template<typename T>
        void RegisterSaveable(ObjectCFunc func)
        {
            static_assert(std::is_base_of<Saveable, T>::value, "Tried to register an object that doesn't derive from uth::Saveable");
            static_assert(!std::is_reference<T>::value && !std::is_pointer<T>::value, "Tried to register an object as pointer or reference. Must be full definition.");

            m_saveableFuncs.emplace(typeid(T).raw_name(), func);
        }

        Saveable* GetSaveable(const rapidjson::Value& val);

        void endScene();

    private:
		void startScene();
		void m_switchScene();
		Scene* (*makeActiveScene)(int SceneID);

		Scene* curScene;

		int m_sceneID;
		int m_nextScene;
		int sceneCount;
		bool m_pendingSceneSwitch;

        std::unordered_map<std::string, ObjectCFunc> m_saveableFuncs;

	};

}
//#include "UtH/Engine/Scenes.inl"
#endif
