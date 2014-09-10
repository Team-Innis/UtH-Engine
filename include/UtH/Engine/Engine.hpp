#pragma once
#ifndef THEHOOD
#define THEHOOD

#include <vector>
#include <UtH/Platform/Singleton.hpp>

#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <UtH/Resources/ResourceManager.h>
#include <UtH/Engine/SceneManager.hpp>
#include <pmath/Vector4.hpp>

#define uthEngine uth::UTHEngine::getInstance()

namespace uth
{
	class UTHEngine : public Singleton<UTHEngine>
	{
		friend class Singleton<UTHEngine>;
	private:
		UTHEngine();

		uth::WindowSettings m_wsettings;
		uth::Window* m_wndw;
		uth::Timer m_timer;
	
		bool m_running;
	
		bool initialize();

        pmath::Vec4 m_clearColor;
	public:
		bool Init();
		bool Init(const uth::WindowSettings &wsettings);
		void Update();
		void Draw();

        void SetClearColor(const pmath::Vec4& color);
        void SetClearColor(float r, float g, float b, float a = 1.0f);

        Window& GetWindow();
		void SetWindow(void* handle);
	
		const pmath::Vec2 GetWindowResolution() const;
		const bool Running() const;
		const Timer timer() const;
	};
}

#endif