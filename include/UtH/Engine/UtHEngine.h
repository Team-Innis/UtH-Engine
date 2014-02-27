#pragma once
#ifndef THEHOOD
#define THEHOOD

#include <vector>
#include <UtH/Platform/Singleton.hpp>

#include <UtH/Platform/Window.hpp>
#include <UtH/Platform/HiResTimer.hpp>

#define theHood uth::UtHEngine::getInstance()
#define Hood uth::UtHEngine::getInstance()

namespace uth
{
	class UtHEngine : public Singleton<UtHEngine>
	{
		UtHEngine();
		~UtHEngine();
		friend class Singleton<UtHEngine>;
	public:
		int AutoMainLoop();
		bool CreateGameWindow(uth::WindowSettings &settings);
		bool Update();
		bool Update(double dt);
		void Draw();

	private:
		bool m_running;
		uth::Window* m_wndw;
		uth::Timer m_timer;
	};
}

#endif