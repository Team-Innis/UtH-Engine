#include <UtH/Platform/Debug.hpp>
#include <cassert>
#include "UtH/Engine/SceneManager.hpp"

namespace uth
{
	
	Scene* defaultNewSceneFunc(SceneManager::SceneName SceneID, Scene* CurScene)
	{
		switch (SceneID)
		{
		case SceneManager::MENU:
			CurScene = new /*Menu*/Scene();
			break;
		case SceneManager::GAME:
			CurScene = new /*Game*/Scene();
			break;
		case SceneManager::CREDITS:
			CurScene = new /*Credits*/Scene();
			break;
		default:
			CurScene = new /*Menu*/Scene();
			break;
		}
		return CurScene;
	}


	SceneManager::SceneManager()
		: m_pendingSceneSwitch(true),
		  m_nextScene(DEFAULT)
	{
		setNewSceneFunc(defaultNewSceneFunc);
		m_switchScene();
	}
	SceneManager::~SceneManager()
	{
		curScene->DeInit();
		delete curScene;
	}
	
	void SceneManager::SwapToScene(SceneName SceneID)
	{
		if (!(DEFAULT <= SceneID && SceneID < COUNT))
		{
			WriteLog("Error when scene %d switching to %d, number out of range, switching to default scene\n",m_sceneID, m_nextScene);
			m_sceneID = DEFAULT;
			return;
		}

		m_sceneID = SceneID;
	}
	void SceneManager::SwapToScene(int SceneNumber)
	{
		SwapToScene((SceneName)SceneNumber);
	}

	bool SceneManager::Update(double dt)
	{
		if (m_pendingSceneSwitch)
			m_switchScene();

		if (!curScene->Update(dt))
		{
			WriteLog("Scene %d Update() func returns false\n",m_sceneID);
			return false;
		}
		return true;
	}
	bool SceneManager::Draw()
	{
		if (!curScene->Draw())
		{
			WriteLog("Scene %d Draw() func returns false\n",m_sceneID);
			return false;
		}
		return true;
	}
	
	void SceneManager::setNewSceneFunc(Scene* (*newSceneFunc)(SceneName SceneID, Scene* CurScene))
	{
		makeActiveScene = newSceneFunc;
	}

	// private
	void SceneManager::endScene()
	{
		if (!curScene->DeInit())
			WriteLog("Scene %d DeInit() func returns false\n",m_sceneID);
		delete curScene;
	}
	void SceneManager::startScene()
	{
		if (curScene->Init())
			m_sceneID = m_nextScene;
		else
		{
			WriteLog("Scene %d Init() func returns false\n",m_sceneID);
			m_nextScene = DEFAULT;
			m_switchScene();
		}
	}

	void SceneManager::m_switchScene()
	{
		if (curScene != nullptr)
			endScene();
		curScene = makeActiveScene(m_nextScene,curScene);
		startScene();
		m_pendingSceneSwitch = false;
	}
	
}