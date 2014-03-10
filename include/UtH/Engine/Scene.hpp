#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

#include <UtH\Core\Shader.hpp>
#include <UtH\Engine\GameObject.hpp>

namespace uth
{
	class Scene
	{
	public:
		friend class SceneManager;
		Scene();
		~Scene();

	public:
		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(double dt);
		virtual bool Draw();

		Shader shader;
		GameObject gameObject;

		int number;
	};
}

#endif
