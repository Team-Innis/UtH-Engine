#pragma once
#ifndef INPUTENUMS_H_UTH
#define INPUTENUMS_H_UTH

namespace uth
{
	namespace Touch
	{
		enum TPattern
		{
			TAP
		};
	}

	namespace Mouse
	{
		enum MButton
		{
			MS1 = 0,
			LEFT = 0,
			MS2 = 1,
			MIDDLE = 1,
			MS3 = 2,
			RIGHT = 2,
			MS4 = 3,
			X1 = 3,
			MS5 = 4,
			X2 = 4,
			COUNT
		};
	}
	
	namespace Keyboard
	{
		enum Key
		{
			BackSpace		  = 0x08,
			Tab				  = 0x09,
			Return			  = 0x0D,
			LeftControl		  = 0x11,
			LeftAlt			  = 0x12,
			Pause			  = 0x13,
			CapsLock		  = 0x14,
			Escape			  = 0x1B,
			Space			  = 0x20,
			PageUp			  = 0x21,
			PageDown		  = 0x22,
			End				  = 0x23,
			Home			  = 0x24,
			Left			  = 0x25,
			Up				  = 0x26,
			Right			  = 0x27,
			Down			  = 0x28,
			PrintScreen		  = 0x2C,
			Insert			  = 0x2D,
			Delete			  = 0x2E,
			Key0			  = 0x30,
			Key1			  = 0x31,
			Key2			  = 0x32,
			Key3			  = 0x33,
			Key4			  = 0x34,
			Key5			  = 0x35,
			Key6			  = 0x36,
			Key7			  = 0x37,
			Key8			  = 0x38,
			Key9			  = 0x39,
			A				  = 0x41,
			B				  = 0x42,
			C				  = 0x43,
			D				  = 0x44,
			E				  = 0x45,
			F				  = 0x46,
			G				  = 0x47,
			H				  = 0x48,
			I				  = 0x49,
			J				  = 0x4A,
			K				  = 0x4B,
			L				  = 0x4C,
			M				  = 0x4D,
			N				  = 0x4E,
			O				  = 0x4F,
			P				  = 0x50,
			Q				  = 0x51,
			R				  = 0x52,
			S				  = 0x53,
			T				  = 0x54,
			U				  = 0x55,
			V				  = 0x56,
			W				  = 0x57,
			X				  = 0x58,
			Y				  = 0x59,
			Z				  = 0x5A,
			Menu			  = 0x5D,
			Numpad0			  = 0x60,
			Numpad1			  = 0x61,
			Numpad2			  = 0x62,
			Numpad3			  = 0x63,
			Numpad4			  = 0x64,
			Numpad5			  = 0x65,
			Numpad6			  = 0x66,
			Numpad7			  = 0x67,
			Numpad8			  = 0x68,
			Numpad9			  = 0x69,
			NumpadMultiply	  = 0x6A,
			NumpadAdd		  = 0x6B,
			NumpadSubtract	  = 0x6D,
			NumpadDecimal	  = 0x6E,
			NumpadDivide	  = 0x6F,
			F1				  = 0x70,
			F2				  = 0x71,
			F3				  = 0x72,
			F4				  = 0x73,
			F5				  = 0x74,
			F6				  = 0x75,
			F7				  = 0x76,
			F8				  = 0x77,
			F9				  = 0x78,
			F10				  = 0x79,
			F11				  = 0x7A,
			F12				  = 0x7B,
			NumLock			  = 0x90,
			ScrollLock		  = 0x91,
			LeftShift		  = 0xA0,
			RightShift		  = 0xA1,
			RightControl	  = 0xA3,
			RightAlt		  = 0xA5,
			LocalSemicolon	  = 0xBA, // ¨
			LocalPlus		  = 0xBB,
			LocalComma		  = 0xBC,
			LocalMinus		  = 0xBD,
			LocalPeriod		  = 0xBE,
			LocalSlash		  = 0xBF, // '
			LocalTilde		  = 0xC0, // ö
			LocalOpenBracket  = 0xDB, // ´
			LocalBackslash	  = 0xDC, // §
			LocalCloseBracket = 0xDD, // å
			LocalQuote		  = 0xDE, // ä
			LocalAngleBracket = 0xE2,
			NumpadEnter		  = 0xFF
		};
	}
	
	namespace UniInput
	{
		enum Happening
		{
			PRESS
		};
	}
}

#endif