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
        // Objects
        RegisterSaveable<Object>();
        RegisterSaveable<GameObject>();
        RegisterSaveable<Camera>();
        RegisterSaveable<SpriteBatch>([](const rapidjson::Value& val) -> Saveable*
        {
            return new SpriteBatch(val["adoptedPointers"].GetBool());
        });
        RegisterSaveable<ParticleSystem>([](const rapidjson::Value& val) -> Saveable*
        {
            return new ParticleSystem(val["particleLimit"].GetUint());
        });
        
        // Components (There should never be any base component instances so no need to register that)
        RegisterSaveable<Rigidbody>([](const rapidjson::Value& val)
        {
            return nullptr; // TODO: Figure out how to actually do this
        });
        RegisterSaveable<Sprite>();
        RegisterSaveable<AnimatedSprite>([](const rapidjson::Value& val)
        {
            return new AnimatedSprite(uthRS.LoadTexture(val["texture"].GetString()),
                                      val["frames"].GetUint(), val["frameCountX"].GetUint(), val["frameCountY"].GetUint());
        });
        RegisterSaveable<Text>([](const rapidjson::Value& val)
        {
            return new Text(val["fontPath"].GetString(), val["fontSize"].GetDouble());
        });

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
            doc.CopyFrom(curScene->save(doc.GetAllocator()), doc.GetAllocator());

            rj::StringBuffer buffer;
            rj::PrettyWriter<rj::StringBuffer> writer(buffer);
            doc.Accept(writer);

            FileManager fm("saves/" + saveName + ".uths", uth::FileManager::Location::INTERNAL, true);
            fm.WriteString(buffer.GetString());

            return true;
        }

        return false;
    }

    bool SceneManager::LoadSavedScene(const std::string& saveName)
    {
        namespace rj = rapidjson;

        FileManager fm;
        const std::string path("saves/" + saveName + ".uths");
        fm.OpenFile(path, uth::FileManager::Location::INTERNAL);
        
        rj::Document doc;
        doc.Parse<0>(fm.ReadText().c_str());

        if (doc.HasParseError())
        {
            WriteError("Failed to parse save file %s", saveName.c_str());
            return false;
        }

        std::unique_ptr<Scene> ptr(static_cast<Scene*>(GetSaveable(doc)));

        if (!ptr)
        {
            WriteError("Failed to cast loaded scene %s", saveName.c_str());
            return false;
        }
        
        if (!ptr->load(doc))
        {
            WriteError("Failed to load one or more objects from save \"%s\"", saveName.c_str());
            return false;
        }

        endScene();
        curScene = ptr.release();
        startScene();

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

    SceneManager& SceneManager::GetInstance()
    {
        static SceneManager instance;

        return instance;
    }

    Saveable* SceneManager::GetSaveable(const rapidjson::Value& val)
    {
        const char* idKey = "identifier";
        if (val.HasMember(idKey) && val[idKey].IsString())
        {
            auto itr = m_saveableFuncs.find(val[idKey].GetString());

            if (itr != m_saveableFuncs.end())
                return itr->second(val);
        }

        WriteError("Failed to cast saveable with.");

        return nullptr;
    }

}