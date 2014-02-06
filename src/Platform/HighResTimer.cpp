#include "UtH/Platform/HighResTimer.hpp"

namespace Scioto
{
	
Timer::Timer()
{
    m_startTime = m_curTime = m_memTime = 0;

	// Initialize

#ifdef WIN32
    QueryPerformanceFrequency(&m_frequency);
    m_startCount.QuadPart = 0;
    m_curCount.QuadPart = 0;
#else
    m_startCount.tv_sec = m_startCount.tv_usec = 0;
    m_curCount.tv_sec = m_curCount.tv_usec = 0;
#endif
	
	// Start
	Reset();
}

void Timer::Reset()
{
#ifdef _WIN32
	m_memTime = 0;
    QueryPerformanceCounter(&m_startCount);
	m_startTime = m_startCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
#else
    gettimeofday(&m_startCount, NULL);
    startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
#endif
}

const long double Timer::GetDeltaTime() // Does Update, calculates difference between this and last GetDeltaTime
{
	long double oldTime = m_memTime;
	return Update() - oldTime;
}

const long double Timer::Update() // Updates memTime to be current time
{
	return m_memTime = GetCurTime();
}

const long double Timer::GetCurTime() // returns time elapsed since timer last restarted
{
#ifdef _WIN32
    QueryPerformanceCounter(&m_curCount);
    m_curTime = m_curCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
#endif

#ifdef __ANDROID__
	gettimeofday(&m_endCount, NULL);
    m_curTime = ((endCount.tv_sec * 1000000.0) + endCount.tv_usec);
#endif
	return (m_curTime - m_startTime) * 0.000001;
}

const long double Timer::GetMemTime() const // returns time from last Update or GetDeltaTime
{
	return m_memTime;
}

#ifdef _WIN32
#endif

#ifdef __ANDROID__
#endif
}