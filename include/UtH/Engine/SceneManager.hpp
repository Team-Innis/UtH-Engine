#ifndef SCENEMANAGER_H_UTH
#define SCENEMANAGER_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Platform/Singleton.hpp>
#include <functional>
#include <unordered_map>
#include <type_traits>

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

        bool SaveCurrentScene(const std::string& saveName);

        bool LoadSavedScene(const std::string& saveName);


        typedef std::function<Object*()> ObjectCFunc;
        typedef std::function<Component*()> ComponentCFunc;

        template<typename T>
        void RegisterObject()
        {
            static_assert(std::is_base_of<Object, T>::value, "Tried to register an object that doesn't derive from uth::Object");
            static_assert(!std::is_reference<T>::value && !std::is_pointer<T>::value, "Tried to register an object as pointer or reference. Must be full definition.");

            m_objectFuncs.emplace(typeid(T).name(), []() -> Object*
            {
                return new T();
            });
        }

        template<typename T>
        void RegisterComponent()
        {
            static_assert(std::is_base_of<Component, T>::value, "Tried to register a component that doesn't derive from uth::Component");
            static_assert(!std::is_reference<T>::value && !std::is_pointer<T>::value, "Tried to register a component as pointer or reference. Must be full definition.");

            m_componentFuncs.emplace(typeid(T).name(), []() -> Component*
            {
                return new T();
            });
        }


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


        friend class Object;
        std::unordered_map<std::string, ObjectCFunc> m_objectFuncs;

        friend class GameObject;
        std::unordered_map<std::string, ComponentCFunc> m_componentFuncs;



	};

}
//#include "UtH/Engine/Scenes.inl"
#endif
