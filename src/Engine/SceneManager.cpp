#include <UtH/Platform/Debug.hpp>
#include <cassert>
#include <UtH/Engine/SceneManager.hpp>

#include <UtH/Engine/DefaultScene.hpp>
#include <UtH/Engine/Engine.hpp>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>


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

    bool SceneManager::SaveCurrentScene(const std::string& saveName)
    {
        namespace rj = rapidjson;

        if (curScene)
        {
            rj::Document doc;
            doc.SetObject();
            
            doc.AddMember(rj::Value(saveName.c_str(), doc.GetAllocator()), curScene->save(doc.GetAllocator()), doc.GetAllocator());

            rj::StringBuffer buffer;
            rj::PrettyWriter<rj::StringBuffer> writer(buffer);
            doc.Accept(writer);
            rj::Value v;

            FileManager fm;
            fm.WriteToFile("saves/" + saveName + ".uths", buffer.GetString());

            return true;
        }

        return false;
    }

    bool SceneManager::LoadSavedScene(const std::string& saveName)
    {
        namespace rj = rapidjson;

        FileManager fm;
        const std::string path("saves/" + saveName + ".uths");
        fm.OpenFile(path);
        
        rj::Document doc;
        doc.Parse<0>(fm.ReadText().c_str());

        if (doc.HasParseError())
        {
            WriteError("Failed to parse save file %s", saveName.c_str());
            return false;
        }

        if (!doc.HasMember(saveName.c_str()))
            return false;

        Scene* ptr = nullptr;
        for (size_t i = 0; i < m_sceneFuncs.size() && ptr == nullptr; ++i)
        {
            if (m_sceneFuncs[i])
                ptr = m_sceneFuncs[i](saveName);
        }

        if (!ptr)
        {
            WriteError("Failed to cast loaded scene %s", saveName.c_str());
            return false;
        }

        if (!ptr->load(doc))
        {
            WriteError("Failed to load one or more objects from save %s", saveName.c_str());
            return false;
        }

        return true;
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