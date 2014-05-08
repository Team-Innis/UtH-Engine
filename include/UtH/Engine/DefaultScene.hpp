#pragma once
#ifndef DefaultScene_H_UTH
#define DefaultScene_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/GameObject.hpp>

namespace uth
{
	class DefaultScene : public Scene
	{
	public:
		friend class SceneManager;
		DefaultScene();
		~DefaultScene();

		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(float dt);
		virtual bool Draw();
	protected:
		Shader* shader;
		float totalTime;
		GameObject* logo;
	};
}

#endif
