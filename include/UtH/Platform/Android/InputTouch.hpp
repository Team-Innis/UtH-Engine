#pragma once
#ifndef TOUCHINPUT_H_UTH
#define TOUCHINPUT_H_UTH

#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Math/Vector2.hpp>

namespace uth
{
	namespace
	{
	class Touches
	{
	public:
		umath::vector2 Position() const { return m_pos;}
	private:
		umath::vector2 m_position;
		bool m_touched;
	};
	}
	class TouchInput
	{
	public:
		Touches ID[8];

		TouchInput()
		{}
		~TouchInput()
		{}
	};
}

#endif