#pragma once
#ifndef JAVAFUNCTIONS_H_UTH
#define JAVAFUNCTIONS_H_UTH

#define javaFunc uth::JavaFunctions

namespace uth
{
	class JavaFunctions
	{
		JavaFunctions();
		~JavaFunctions();
	public:
		// Vibrates for given time in milliseconds.
		static void Vibrate(int time_ms);
		static void ShowAd(){}
	private:


	};
}
#endif