#pragma once
#ifndef THEHOOD
#define THEHOOD

#include <vector>
#include <UtH\Platform\Singleton.hpp>
#include <UtH\Engine\Scene.hpp>

#define theHood uth::UtHEngine::getInstance()
#define Hood uth::UtHEngine::getInstance()
#define ö Hood.AutoMainLoop()

namespace uth
{
	class UtHEngine : public Singleton<UtHEngine>
	{
		UtHEngine();
		~UtHEngine();
		friend class Singleton<UtHEngine>;
	public:
		int AutoMainLoop();
		bool CreateGameWindow();
		bool Update();
		void Draw();

	private:
		bool m_running;
	};
}

#endif