#pragma once
#ifndef JAVAFUNCTIONS_H_UTH
#define JAVAFUNCTIONS_H_UTH

#define javaFunc uth::JavaFunctions

#include <pmath/PMath.hpp>

namespace uth
{
	class JavaFunctions
	{
		JavaFunctions();
		~JavaFunctions();
	public:
		// Vibrates for given time in milliseconds.
		static void Vibrate(int time_ms);
		static void ShowAd(unsigned int origin, pmath::Vec2i offset = pmath::Vec2i()){}
		static void CloseAd(unsigned int origin = 0){}
	private:


	};
}
#endif