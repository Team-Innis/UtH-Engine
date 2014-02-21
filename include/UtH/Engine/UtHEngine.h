#pragma once
#ifndef THEHOOD
#define THEHOOD

#include <vector>
#include <UtH\Platform\Singleton.hpp>

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
		bool CreateGameWindow();
		bool Update();
		void Draw();

	private:
		bool m_running;
	};
}

#endif