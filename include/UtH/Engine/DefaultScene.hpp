#pragma once
#ifndef DEFAULTSCENE_H_UTH
#define DEFAULTSCENE_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Renderer/SpriteBatch.hpp>

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

		Shader shader,
            bShader;
		Camera camera;
        std::vector<GameObject*> objects;
        GameObject obj;
        SpriteBatch batch;

        TextureAtlas atlas;

		int number;
	};
}

#endif
