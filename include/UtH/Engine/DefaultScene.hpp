#pragma once
#ifndef DEFAULTSCENE_H_UTH
#define DEFAULTSCENE_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Renderer/Camera.hpp>

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

		virtual bool Update(double dt);
		virtual bool Draw();
	protected:
		Shader shader;
		Camera camera;
		GameObject gameObject, textObject;
		GameObject gameObject2;

		int number;
	};
}

#endif
