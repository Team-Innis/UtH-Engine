#include <UtH/Platform/Debug.hpp>
#include <cassert>
#include <UtH/Engine/SceneManager.hpp>

#include <UtH/Engine/DefaultScene.hpp>
#include <UtH/Engine/Engine.hpp>


namespace uth
{
	Scene* defaultNewSceneFunc(int SceneID)
	{
		return nullptr;
	}

	SceneManager::SceneManager()
		: m_nextScene(UTHDefaultScene),
		  m_pendingSceneSwitch(true)
	{
		registerNewSceneFunc(defaultNewSceneFunc, 0);
	}
	SceneManager::~SceneManager()
	{
		curScene->DeInit();
		delete curScene;
	}
	
	void SceneManager::GoToScene(int SceneID, bool /*disposeCurrent*/)
	{
		// TODO:
        // disposeCurrent;
		if (!(UTHDefaultScene <= SceneID && SceneID < sceneCount))
		{
			WriteError("Error when scene %d switching to %d, number out of range, switching to default scene",m_sceneID, m_nextScene);
			m_sceneID = -1;
			return;
		}
		m_pendingSceneSwitch = true;
		m_nextScene = SceneID;
	}

	void SceneManager::Update(float dt)
	{
		if (m_pendingSceneSwitch)
			m_switchScene();

		curScene->Update(dt);
	}

	void SceneManager::Draw()
	{
		curScene->Draw(uthEngine.GetWindow());
	}
	
	void SceneManager::registerNewSceneFunc(Scene* (*newSceneFunc)(int SceneID), int SceneCount)
	{
		makeActiveScene = newSceneFunc;
		sceneCount = SceneCount;
    }

    namespace x = tinyxml2;

    bool SceneManager::SaveCurrentScene(const std::string& saveName, const std::string& path)
    {
        x::XMLDocument doc;
        doc.ToElement()->SetName("savename");
        doc.ToElement()->SetValue(saveName.c_str());
        
        doc.InsertEndChild(curScene->Object::save());

        FileManager().WriteToFile(path + "/" + saveName, doc.ToText()->Value());

        return true;
    }

    bool SceneManager::LoadSavedScene(const std::string& path)
    {
        FileManager fm;
        fm.OpenFile(path);
        
        x::XMLDocument doc;
        if (doc.Parse(fm.ReadText().c_str()))
        {
            WriteError("Failed to parse save file in path %s", path.c_str());
            return false;
        }

        // Why tinyxml so confusing...
        const std::string sceneName(doc.ToElement()->Value());

        Scene* ptr = nullptr;
        for (size_t i = 0; i < m_sceneFuncs.size() && ptr == nullptr; ++i)
        {
            if (m_sceneFuncs[i])
                ptr = m_sceneFuncs[i](sceneName);
        }

        if (!ptr)
        {
            WriteError("Failed to cast loaded scene (%s)", sceneName.c_str());
            return false;
        }

        bool error = false;
        for (auto itr = doc.FirstChildElement(); itr != nullptr; itr = itr->NextSiblingElement())
        {
            auto obj = std::make_shared<Object>();
            
            if (obj->load(*itr))
                ptr->AddChild(obj);
            else
                error = true;
        }

        if (error)
        {
            WriteError("Failed to load one or more objects from save %s", path.c_str());
        }

        ptr->SetActive(true);

        return !error;
    }


	// private
	void SceneManager::endScene()
	{
		if (!curScene->DeInit())
			WriteError("Scene %d DeInit() func returns false",m_sceneID);
		delete curScene;
	}
	void SceneManager::startScene()
	{
		if (curScene->Init())
			m_sceneID = m_nextScene;
		else
		{
			WriteError("Scene %d Init() func returns false",m_sceneID);
			m_nextScene = -1;
			m_switchScene();
		}
	}

	void SceneManager::m_switchScene()
	{
		if (curScene != nullptr)
			endScene();
		Scene* newScene = makeActiveScene(m_nextScene);
		if (newScene)
			curScene = newScene;
		else
			curScene = new uth::DefaultScene();
		startScene();
		m_pendingSceneSwitch = false;
	}

    void SceneManager::AddSceneCreateFunc(SceneCFunc func)
    {
        m_sceneFuncs.emplace_back(func);
    }

    void SceneManager::AddObjectCreateFunc(ObjectCFunc func)
    {
        m_objectFuncs.emplace_back(func);
    }

    void SceneManager::AddComponentCreateFunc(ComponentCFunc func)
    {
        m_componentFuncs.emplace_back(func);
    }

}