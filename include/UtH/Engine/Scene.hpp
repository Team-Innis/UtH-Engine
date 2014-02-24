#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Core\Shader.hpp>
#include <iostream>
#include <Windows.h>
#include <UtH\Core\VertexBuffer.hpp>
#include <UtH\Renderer\Texture.hpp>

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

		uth::WindowSettings* settings;
		uth::Shader* shader;
		uth::VertexBuffer* buf;
		uth::Texture* tex;

		int number;
	};
}

#endif
