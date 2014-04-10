#pragma once
#ifndef COMMONINPUT_H_UTH
#define COMMONINPUT_H_UTH
//Android
#include <UtH/Platform/Common/InputBase.hpp>
#include <UtH/Math/Vector2.hpp>

namespace uth
{
	enum class InputEvent
	{
		NONE = 0,
		STATIONARY,
		CLICK,
		TAP = CLICK,
		DRAG,
		ZOOM_IN,
		ZOOM_OUT
	};

	class CommonInput : public InputBase
	{
	private:
		InputEvent m_event;
		umath::vector2 m_position;
	public:
		const InputEvent& Event() const;
		const umath::vector2 Position() const;
		
		void Update();
		
		bool operator == (InputEvent Event);
		bool operator != (InputEvent Event);
	};
}

#endif