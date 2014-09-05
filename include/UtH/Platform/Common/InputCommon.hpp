#pragma once
#ifndef INPUTCOMMON_H_UTH
#define INPUTCOMMON_H_UTH
//Windows
#include <UtH/Platform/Common/InputBase.hpp>
#include <pmath/Vector2.hpp>

namespace uth
{
	enum InputEvent
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
		pmath::Vec2 m_position;
	public:
		const InputEvent& Event() const;
		const pmath::Vec2 Position() const;
		
		void Update();
		
        // Use with uthInput.Common == Event
		bool operator == (const InputEvent& Event) const;
		bool operator != (const InputEvent& Event) const;
	};
}

#endif