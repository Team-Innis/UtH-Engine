#pragma once
#ifndef THEHOOD
#define THEHOOD

#include <vector>
#include <UtH/Platform/Singleton.hpp>
#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <pmath/Vector4.hpp>

#include <UtH/Engine/Particles/ParticleSystem.hpp>
#include <UtH/Engine/TMX/Map.hpp>
#include <UtH/Engine/TMX/ObjectGroup.hpp>

#include <UtH/Engine/SceneManager.hpp>
#include <UtH/Engine/DefaultScene.hpp>
#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Engine/Physics/PhysicsContactListener.hpp>
#include <UtH/Engine/Physics/PhysicsWorld.hpp>
#include <UtH/Engine/SceneManager.hpp>
#include <UtH/Engine/SpriteBatch.hpp>

//#include <UtH/Resources/ResourceManager.hpp>

#define uthEngine uth::Engine::getInstance()

namespace uth
{
	class Engine : public Singleton<Engine>
	{
		friend class Singleton<Engine>;
	private:
		Engine();

		uth::WindowSettings m_wsettings;
		uth::Window* m_wndw;
		uth::Timer m_timer;
	
		bool m_running;
	
		bool initialize();

        pmath::Vec4 m_clearColor;
	public:
		bool Init(const uth::WindowSettings &wsettings = uth::WindowSettings());
		void Update();
		void Draw();

		void Exit();

        void SetClearColor(const pmath::Vec4& color);
        void SetClearColor(float r, float g, float b, float a = 1.0f);

        Window& GetWindow();
		void SetWindow(void* handle);
	
		const pmath::Vec2 GetWindowResolution() const;
		const bool Running() const;
		const Timer& Timer() const;
	};
}

#endif