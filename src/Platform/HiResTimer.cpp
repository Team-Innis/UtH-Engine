#include <UtH/Platform/HiResTimer.hpp>

namespace uth
{

	Timer::Timer()
	{
		m_startTime = m_curTime = m_memTime = 0;

#if defined(UTH_SYSTEM_WINDOWS)
		QueryPerformanceFrequency(&m_frequency);
		m_startCount.QuadPart = 0;
		m_curCount.QuadPart = 0;
#elif defined(UTH_SYSTEM_POSIX)
		m_startCount.tv_sec = m_startCount.tv_usec = 0;
		m_curCount.tv_sec = m_curCount.tv_usec = 0;
#endif

		Reset();
	}

	const long double Timer::Reset()
	{
		const long double curTime = CurTime();
#if defined(UTH_SYSTEM_WINDOWS)
		m_memTime = 0;
		QueryPerformanceCounter(&m_startCount);
		m_startTime = m_startCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
#elif defined(UTH_SYSTEM_POSIX)
		gettimeofday(&m_startCount, 0);
		m_startTime = (m_startCount.tv_sec * 1000000.0) + m_startCount.tv_usec;
#endif
		return curTime;
	}

	const long double Timer::DeltaTime()
	{
		const long double oldTime = m_memTime;
		return Update() - oldTime;
	}

	const long double Timer::Update()
	{
		return m_memTime = CurTime();
	}

	const long double Timer::CurTime()
	{
#if defined(UTH_SYSTEM_WINDOWS)
		QueryPerformanceCounter(&m_curCount);
		m_curTime = m_curCount.QuadPart * (1000000.0 / m_frequency.QuadPart);
#elif defined(UTH_SYSTEM_POSIX)
		gettimeofday(&m_curCount, 0);
		m_curTime = ((m_curCount.tv_sec * 1000000.0) + m_curCount.tv_usec);
#endif
		return (m_curTime - m_startTime) * 0.000001;
	}

	const long double Timer::GetMemTime() const
	{
		return m_memTime;
	}

}
