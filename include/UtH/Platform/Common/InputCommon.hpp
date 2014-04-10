#pragma once
#ifndef INPUTCOMMON_H_UTH
#define INPUTCOMMON_H_UTH
//Windows
#include <UtH/Platform/Common/InputBase.hpp>

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

	public:
	};
}

#endif