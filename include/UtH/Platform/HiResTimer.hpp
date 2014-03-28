#pragma once
#ifndef UTILS_H_UTH
#define UTILS_H_UTH

#include <UtH/Platform/Configuration.hpp>

#if defined(UTH_SYSTEM_WINDOWS)
#include <windows.h>

#elif defined(UTH_SYSTEM_ANDROID) || defined(UTH_)
#include <sys/time.h>
#endif

namespace uth
{
	class Timer
	{
	public:
		Timer(); //initializes Timer class
		/**
		Sets timer start and memtime to current time, returns time since last reset
		*/
		const long double Reset();
		/**
		Updates memtime, returns the difference: "DeltaTime"
		*/
		const long double DeltaTime();
		/**
		Updates memtime, returns total running time
		*/
		const long double Update();
		/**
		Returns total running time since timer start
		*/
		const long double CurTime();
		/**
		Returns the total running time until last Update() event
		*/
		const long double GetMemTime() const;

	private:
		long double m_startTime;
		long double m_memTime;
		long double m_curTime;
		
#if defined(UTH_SYSTEM_WINDOWS)
		LARGE_INTEGER m_frequency;
		LARGE_INTEGER m_startCount;
		LARGE_INTEGER m_curCount;

#elif defined(UTH_SYSTEM_ANDROID)
		timeval m_startCount;
		timeval m_curCount;

#endif

	};
}

#endif