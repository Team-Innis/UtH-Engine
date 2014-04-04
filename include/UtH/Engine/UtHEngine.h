#pragma once
#ifndef THEHOOD
#define THEHOOD

#include <vector>
#include <UtH/Platform/Singleton.hpp>

#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/HiResTimer.hpp>
#include <UtH/Resources/ResourceManager.h>
#include <UtH/Engine/SceneManager.hpp>

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
	public:
		bool Init();
		bool Init(const uth::WindowSettings &wsettings);
		void Update();
		void Draw();

        Window& GetWindow();
	
		const umath::vector2 GetWindowResolution() const;
		const bool Running() const;
		const Timer timer() const;
	};
}

#endif