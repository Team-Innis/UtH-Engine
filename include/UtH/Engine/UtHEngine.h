#ifndef THEHOOD
#define THEHOOD

#include <vector>
#include <UtH\Platform\Singleton.hpp>


namespace uth
{
	class UtHEngine : public Singleton<UtHEngine>
	{
	public:
		UtHEngine();
		~UtHEngine();
		bool CreateGameWindow();
		void Update();
		void Draw();

	private:
		bool m_running;
	};
}

#endif