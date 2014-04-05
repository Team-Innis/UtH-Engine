#pragma once
#ifndef TestScene_H_UTH
#define TestScene_H_UTH

#include <vector>
#include <UtH/Engine/Scene.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <UtH/Renderer/RenderTexture.hpp>

namespace uth
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(float dt);
		virtual bool Draw();
	protected:
		Shader* shader;
		Camera camera;

		std::vector<GameObject*> gameObjects;
        RenderTexture rtex;

        GameObject* rtexSprite;

        GameObject* obj;

		int number;

		Timer timer;

		b2Body* groundBody;
	};
}

#endif
