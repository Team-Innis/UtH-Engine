#pragma once
#ifndef JAVAFUNCTIONS_H_UTH
#define JAVAFUNCTIONS_H_UTH

#include <UtH/Platform/Singleton.hpp>

#define javaFunc uth::JavaFunctions

namespace uth
{
	class JavaFunctions
	{
		JavaFunctions();
		~JavaFunctions();
		friend class Singleton < JavaFunctions >;
	public:
		// Vibrates for given time in milliseconds.
		static void Vibrate(int time_ms);

	private:


	};
}
#endif