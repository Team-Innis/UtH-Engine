#pragma once
#ifndef INPUTENUMS_H_UTH
#define INPUTENUMS_H_UTH

//#include <GLFW/glfw3.h>

namespace uth
{
	namespace Touch
	{
		enum TPattern
		{
			TAP,
			SEPARATE
		};
	}

	namespace Mouse
	{
		enum MButton
		{
			MS1		= 0,
			LEFT	= MS1,
			MS2		= 1,
			RIGHT	= MS2,
			MS3		= 2,
			MIDDLE	= MS3,
			MS4		= 3,
			X1		= MS4,
			MS5		= 4,
			X2		= MS5,
			COUNT
		};
	}
	
	namespace Keyboard
	{
		enum Key
		{
			BackSpace			,
			Tab					,
			Return				,
			LeftControl			,
			LeftAlt				,
			Pause				,
			CapsLock			,
			Escape				,
			Space				,
			PageUp				,
			PageDown			,
			End					,
			Home				,
			Left				,
			Up					,
			Right				,
			Down				,
			PrintScreen			,
			Insert				,
			Delete				,
			Key0				,
			Key1				,
			Key2				,
			Key3				,
			Key4				,
			Key5				,
			Key6				,
			Key7				,
			Key8				,
			Key9				,
			A					,
			B					,
			C					,
			D					,
			E					,
			F					,
			G					,
			H					,
			I					,
			J					,
			K					,
			L					,
			M					,
			N					,
			O					,
			P					,
			Q					,
			R					,
			S					,
			T					,
			U					,
			V					,
			W					,
			X					,
			Y					,
			Z					,
			Menu				,
			Numpad0				,
			Numpad1				,
			Numpad2				,
			Numpad3				,
			Numpad4				,
			Numpad5				,
			Numpad6				,
			Numpad7				,
			Numpad8				,
			Numpad9				,
			NumpadMultiply		,
			NumpadAdd			,
			NumpadSubtract		,
			NumpadDecimal		,
			NumpadDivide		,
			F1					,
			F2					,
			F3					,
			F4					,
			F5					,
			F6					,
			F7					,
			F8					,
			F9					,
			F10					,
			F11					,
			F12					,
			NumLock				,
			ScrollLock			,
			LeftShift			,
			RightShift			,
			RightControl		,
			RightAlt			,
			//LocalSemicolon	  = 0xBA, // ¨
			//LocalPlus		  = 0xBB,
			LocalComma			,
			//LocalMinus		,
			//LocalPeriod		,
			//LocalSlash		, // '
			//LocalTilde		, // ö
			LocalOpenBracket	, // ´
			//LocalBackslash	  = 0xDC, // §
			LocalCloseBracket	, // å
			LocalQuote			, // ä
			//LocalAngleBracket = 0xE2,
			NumpadEnter			,
			COUNT
		};
	}
	
	namespace UniInput
	{
		enum Happening
		{
			CLICK	= 0,
			CLICK_ALTERNATIVE = 1,
			DOUBLECLICK = 2
		};
	}
}

#endif