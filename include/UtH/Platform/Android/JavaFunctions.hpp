#pragma once
#ifndef JAVAFUNCTIONS_H_UTH
#define JAVAFUNCTIONS_H_UTH
// ANDROID

#define javaFunc uth::JavaFunctions

#include <pmath/PMath.hpp>

namespace uth
{
	class JavaFunctions
	{
		JavaFunctions();
		~JavaFunctions();
	public:
		static void Vibrate(int time_ms);
		static void ShowAd(unsigned int origin, pmath::Vec2i offset = pmath::Vec2i(), std::string name = "");
		static void CloseAd(const std::string& name);
	private:


	};
}
#endif