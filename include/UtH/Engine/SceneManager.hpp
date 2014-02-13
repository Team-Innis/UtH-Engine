#include "UtH/Engine/Scene.hpp"
#ifndef SCENEMANAGER_HPP_UTH
#define SCENEMANAGER_HPP_UTH

#include <UtH/Platform/Singleton.hpp>

namespace uth
{

	class SceneManager : public Singleton<SceneManager>
	{
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
		bool makeActiveScene(int SceneID);

	public:
		
#include "UtH/Engine/SceneManager.h"
		void SwapToScene(SceneName SceneID);
		void SwapToScene(int SceneNumber);

		bool Update(double dt);
		bool Draw();

	private:

		void m_switchScene();

		//Scene* curScene;
		SceneName m_sceneID;
		SceneName m_nextScene;
		bool m_pendingSceneSwitch;


	};

}
#endif
