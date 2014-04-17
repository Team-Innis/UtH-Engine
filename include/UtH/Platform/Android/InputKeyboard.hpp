#pragma once
#ifndef KEYBOARDINPUT_H_UTH
#define KEYBOARDINPUT_H_UTH

#include <UtH/Platform/InputEnums.hpp>
#include <UtH/Platform/Common/InputBase.hpp>

namespace uth
{
	namespace Keyboard
	{
		enum class Key
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

	class KeyboardInput : public InputBase
	{
	public:
		KeyboardInput();
		~KeyboardInput();
		
		void Initiate();
		void Update();

		bool IsKeyDown(Keyboard::Key key);
		bool IsKeyPressed(Keyboard::Key key);
		bool IsKeyReleased(Keyboard::Key key);

	};
}

#endif