#include <UtH/Platform/Debug.hpp>
#include <cassert>
#include "UtH/Engine/SceneManager.hpp"

namespace uth
{
	SceneManager::SceneManager()
		: m_pendingSceneSwitch(true),
		  m_nextScene(DEFAULT)
	{
		
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

	void SceneManager::m_switchScene()
	{
		if (!curScene->DeInit())
			WriteLog("Scene %d DeInit() func returns false\n",m_sceneID);
		delete curScene;

		makeActiveScene(m_nextScene);

		if (curScene->Init())
			m_sceneID = m_nextScene;
		else
		{
			WriteLog("Scene %d Init() func returns false\n",m_sceneID);
			m_nextScene = DEFAULT;
			m_switchScene();
		}
	}
}