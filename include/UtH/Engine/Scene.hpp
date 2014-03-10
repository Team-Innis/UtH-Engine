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
		virtual bool Init() = 0;
		virtual bool DeInit() = 0;

		virtual bool Update(double dt) = 0;
		virtual bool Draw() = 0;
	};
}

#endif
