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
#include <UtH/Engine/TMX/Map.hpp>


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

        TextureAtlas atlas;
        SpriteBatch batch;

        GameObject* rtexSprite;

        GameObject* obj;
		
		TMX::Map* map;

		int number;

		Timer timer;

		b2Body* groundBody;

        ParticleSystem pSystem;
	};
}

#endif
