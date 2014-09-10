#pragma once
#ifndef TestScene_H_UTH
#define TestScene_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Particles/ParticleSystem.hpp>

#include <UtH/Audio/Sound.hpp>
#include <UtH/Platform/Input.hpp>

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

		GameObject *test;

        ParticleSystem ps;

		
		Sound* music;

	};
}

#endif
