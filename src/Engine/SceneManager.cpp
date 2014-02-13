#include "UtH/Engine/SceneManager.hpp"
#include <UtH/Platform/Debug.hpp>

namespace uth
{
	SceneManager::SceneManager()
		: m_pendingSceneSwitch(true)
	{

	}
	SceneManager::~SceneManager()
	{
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
			WriteLog("Error in scene %d Update() func\n",m_sceneID);
			return false;
		}
		return true;
	}
	bool SceneManager::Draw()
	{
		if (!curScene->Draw())
		{
			WriteLog("Error in scene %d Draw() func\n",m_sceneID);
			return false;
		}
		return true;
	}

	void SceneManager::m_switchScene()
	{
		delete curScene;
		curScene->DeInit();
		makeActiveScene(m_nextScene);
		curScene->Init();
		m_sceneID = m_nextScene;
	}
}