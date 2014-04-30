#pragma once
#ifndef TestScene_H_UTH
#define TestScene_H_UTH

#include <vector>
#include <UtH/Engine/Scene.hpp>
#include <UtH/Renderer/Camera.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <UtH/Renderer/RenderTexture.hpp>
#include <UtH/Engine/SpriteBatch.hpp>
#include <UtH/Engine/Particles/ParticleSystem.hpp>

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

		// Particles
        ParticleSystem pSystem;

		// Render texture
        RenderTexture rtex;
        GameObject* rtexSprite;



		std::vector<GameObject*> gameObjects;

        TextureAtlas atlas;
        SpriteBatch batch;

		GameObject* go;

        GameObject* obj;

		int number;

		b2Body* groundBody;

	};
}

#endif
