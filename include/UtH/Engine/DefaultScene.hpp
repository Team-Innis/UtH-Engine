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

	public:
		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(double dt);
		virtual bool Draw();

		Shader shader;
		Camera camera;
		GameObject gameObject;

		int number;
	};
}

#endif