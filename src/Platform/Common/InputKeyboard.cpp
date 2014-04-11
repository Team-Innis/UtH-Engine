#include <UtH/Platform/Common/InputKeyboard.hpp>
#include <GLFW/glfw3.h>



namespace uth
{

	static int KEYBOARD[uth::Keyboard::Key::COUNT];

	void keyCallBack(GLFWwindow *, int, int, int, int);


	KeyboardInput::KeyboardInput()
		: m_keys(Keyboard::Key::COUNT, false),
		m_Lkeys(Keyboard::Key::COUNT, false)
	{
		for(int i = 0; i < Keyboard::Key::COUNT; i++)
		{
			KEYBOARD[i] = 0;
		}
	}

	KeyboardInput::~KeyboardInput()
	{
	}

	void KeyboardInput::Initiate()
	{
		GLFWwindow *window = static_cast<GLFWwindow*>(windowHandle);
		glfwSetKeyCallback(window,keyCallBack);
		//glfwSetInputMode(window,GLFW_STICKY_KEYS,GL_TRUE);

	}
	void KeyboardInput::Update()
	{
		std::memcpy(&m_Lkeys[0],&m_keys[0],Keyboard::Key::COUNT * sizeof(int));
		std::memcpy(&m_keys[0],&KEYBOARD[0],Keyboard::Key::COUNT * sizeof(int));
	}


	bool KeyboardInput::IsKeyDown(Keyboard::Key key)
	{
		return m_keys[key] != 0;
	}
	bool KeyboardInput::IsKeyPressed(Keyboard::Key key)
	{
		return m_keys[key] != 0 && m_Lkeys[key] == 0;
	}
	bool KeyboardInput::IsKeyReleased(Keyboard::Key key)
	{
		return m_keys[key] == 0 && m_Lkeys[key] != 0;
	}


	void keyCallBack(GLFWwindow *, int keyboardKey, int, int action, int)
	{
		int errorint = -1;
		int* keyPtr = &errorint;

#pragma region KeyRefFech
		switch (keyboardKey)
		{
		case GLFW_KEY_BACKSPACE:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::BackSpace];
			break;
		case GLFW_KEY_TAB:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Tab];
			break;
		case GLFW_KEY_ENTER:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Return];
			break;
		case GLFW_KEY_LEFT_CONTROL:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LeftControl];
			break;
		case GLFW_KEY_LEFT_ALT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LeftAlt];
			break;
		case GLFW_KEY_PAUSE:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Pause];
			break;
		case GLFW_KEY_CAPS_LOCK:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::CapsLock];
			break;
		case GLFW_KEY_ESCAPE:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Escape];
			break;
		case GLFW_KEY_SPACE:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Space];
			break;
		case GLFW_KEY_PAGE_UP:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::PageUp];
			break;
		case GLFW_KEY_PAGE_DOWN:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::PageDown];
			break;
		case GLFW_KEY_END:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::End];
			break;
		case GLFW_KEY_HOME:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Home];
			break;
		case GLFW_KEY_LEFT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Left];
			break;
		case GLFW_KEY_UP:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Up];
			break;
		case GLFW_KEY_RIGHT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Right];
			break;
		case GLFW_KEY_DOWN:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Down];
			break;
		case GLFW_KEY_PRINT_SCREEN:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::PrintScreen];
			break;
		case GLFW_KEY_INSERT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Insert];
			break;
		case GLFW_KEY_DELETE:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Delete];
			break;
		case GLFW_KEY_0:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key0];
			break;
		case GLFW_KEY_1:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key1];
			break;
		case GLFW_KEY_2:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key2];
			break;
		case GLFW_KEY_3:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key3];
			break;
		case GLFW_KEY_4:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key4];
			break;
		case GLFW_KEY_5:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key5];
			break;
		case GLFW_KEY_6:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key6];
			break;
		case GLFW_KEY_7:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key7];
			break;
		case GLFW_KEY_8:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key8];
			break;
		case GLFW_KEY_9:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Key9];
			break;
		case GLFW_KEY_A:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::A];
			break;
		case GLFW_KEY_B:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::B];
			break;
		case GLFW_KEY_C:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::C];
			break;
		case GLFW_KEY_D:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::D];
			break;
		case GLFW_KEY_E:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::E];
			break;
		case GLFW_KEY_F:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F];
			break;
		case GLFW_KEY_G:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::G];
			break;
		case GLFW_KEY_H:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::H];
			break;
		case GLFW_KEY_I:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::I];
			break;
		case GLFW_KEY_J:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::J];
			break;
		case GLFW_KEY_K:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::K];
			break;
		case GLFW_KEY_L:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::L];
			break;
		case GLFW_KEY_M:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::M];
			break;
		case GLFW_KEY_N:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::N];
			break;
		case GLFW_KEY_O:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::O];
			break;
		case GLFW_KEY_P:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::P];
			break;
		case GLFW_KEY_Q:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Q];
			break;
		case GLFW_KEY_R:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::R];
			break;
		case GLFW_KEY_S:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::S];
			break;
		case GLFW_KEY_T:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::T];
			break;
		case GLFW_KEY_U:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::U];
			break;
		case GLFW_KEY_V:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::V];
			break;
		case GLFW_KEY_W:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::W];
			break;
		case GLFW_KEY_X:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::X];
			break;
		case GLFW_KEY_Y:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Y];
			break;
		case GLFW_KEY_Z:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Z];
			break;
		case GLFW_KEY_MENU:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Menu];
			break;
		case GLFW_KEY_KP_0:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad0];
			break;
		case GLFW_KEY_KP_1:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad1];
			break;
		case GLFW_KEY_KP_2:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad2];
			break;
		case GLFW_KEY_KP_3:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad3];
			break;
		case GLFW_KEY_KP_4:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad4];
			break;
		case GLFW_KEY_KP_5:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad5];
			break;
		case GLFW_KEY_KP_6:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad6];
			break;
		case GLFW_KEY_KP_7:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad7];
			break;
		case GLFW_KEY_KP_8:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad8];
			break;
		case GLFW_KEY_KP_9:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::Numpad9];
			break;
		case GLFW_KEY_KP_MULTIPLY:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumpadMultiply];
			break;
		case GLFW_KEY_KP_ADD:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumpadAdd];
			break;
		case GLFW_KEY_KP_SUBTRACT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumpadSubtract];
			break;
		case GLFW_KEY_KP_DECIMAL:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumpadDecimal];
			break;
		case GLFW_KEY_KP_DIVIDE:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumpadDivide];
			break;
		case GLFW_KEY_F1:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F1];
			break;
		case GLFW_KEY_F2:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F2];
			break;
		case GLFW_KEY_F3:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F3];
			break;
		case GLFW_KEY_F4:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F4];
			break;
		case GLFW_KEY_F5:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F5];
			break;
		case GLFW_KEY_F6:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F6];
			break;
		case GLFW_KEY_F7:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F7];
			break;
		case GLFW_KEY_F8:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F8];
			break;
		case GLFW_KEY_F9:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F9];
			break;
		case GLFW_KEY_F10:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F10];
			break;
		case GLFW_KEY_F11:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F11];
			break;
		case GLFW_KEY_F12:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::F12];
			break;
		case GLFW_KEY_NUM_LOCK:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumLock];
			break;
		case GLFW_KEY_SCROLL_LOCK:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::ScrollLock];
			break;
		case GLFW_KEY_LEFT_SHIFT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LeftShift];
			break;
		case GLFW_KEY_RIGHT_SHIFT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::RightShift];
			break;
		case GLFW_KEY_RIGHT_CONTROL:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::RightControl];
			break;
		case GLFW_KEY_RIGHT_ALT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::RightAlt];
			break;
		case GLFW_KEY_SEMICOLON:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalSemicolon];
			break;
		case GLFW_KEY_EQUAL:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalPlus];
			break;
		case GLFW_KEY_COMMA:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalComma];
			break;
		case GLFW_KEY_MINUS:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalMinus];
			break;
		case GLFW_KEY_PERIOD:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalPeriod];
			break;
		case GLFW_KEY_SLASH:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalSlash];
			break;
		case GLFW_KEY_GRAVE_ACCENT:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalTilde];
			break;
		case GLFW_KEY_LEFT_BRACKET:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalOpenBracket];
			break;
		case GLFW_KEY_BACKSLASH:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalBackslash];
			break;
		case GLFW_KEY_RIGHT_BRACKET:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalCloseBracket];
			break;
		case GLFW_KEY_APOSTROPHE:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalQuote];
			break;
		case GLFW_KEY_WORLD_2:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LocalAngleBracket];
			break;
		case GLFW_KEY_LEFT_SUPER:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::LeftSuper];
			break;
		case GLFW_KEY_RIGHT_SUPER:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::RightSuper];
			break;
		case GLFW_KEY_KP_ENTER:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumpadEnter];
			break;
		case GLFW_KEY_WORLD_1:
			keyPtr = &KEYBOARD[uth::Keyboard::Key::NumpadEnter];
			break;
		default:
			break;
		}
#pragma endregion KeyRefFech

		(*keyPtr) = action;

	}


	
	namespace glfwKeys
	{
		enum Key
		{
			BackSpace		  = GLFW_KEY_BACKSPACE,
			Tab				  = GLFW_KEY_TAB,
			Return			  = GLFW_KEY_ENTER,
			LeftControl		  = GLFW_KEY_LEFT_CONTROL,
			LeftAlt			  = GLFW_KEY_LEFT_ALT,
			Pause			  = GLFW_KEY_PAUSE,
			CapsLock		  = GLFW_KEY_CAPS_LOCK,
			Escape			  = GLFW_KEY_ESCAPE,
			Space			  = GLFW_KEY_SPACE,
			PageUp			  = GLFW_KEY_PAGE_UP,
			PageDown		  = GLFW_KEY_PAGE_DOWN,
			End				  = GLFW_KEY_END,
			Home			  = GLFW_KEY_HOME,
			Left			  = GLFW_KEY_LEFT,
			Up				  = GLFW_KEY_UP,
			Right			  = GLFW_KEY_RIGHT,
			Down			  = GLFW_KEY_DOWN,
			PrintScreen		  = GLFW_KEY_PRINT_SCREEN,
			Insert			  = GLFW_KEY_INSERT,
			Delete			  = GLFW_KEY_DELETE,
			Key0			  = GLFW_KEY_0,
			Key1			  = GLFW_KEY_1,
			Key2			  = GLFW_KEY_2,
			Key3			  = GLFW_KEY_3,
			Key4			  = GLFW_KEY_4,
			Key5			  = GLFW_KEY_5,
			Key6			  = GLFW_KEY_6,
			Key7			  = GLFW_KEY_7,
			Key8			  = GLFW_KEY_8,
			Key9			  = GLFW_KEY_9,
			A				  = GLFW_KEY_A,
			B				  = GLFW_KEY_B,
			C				  = GLFW_KEY_C,
			D				  = GLFW_KEY_D,
			E				  = GLFW_KEY_E,
			F				  = GLFW_KEY_F,
			G				  = GLFW_KEY_G,
			H				  = GLFW_KEY_H,
			I				  = GLFW_KEY_I,
			J				  = GLFW_KEY_J,
			K				  = GLFW_KEY_K,
			L				  = GLFW_KEY_L,
			M				  = GLFW_KEY_M,
			N				  = GLFW_KEY_N,
			O				  = GLFW_KEY_O,
			P				  = GLFW_KEY_P,
			Q				  = GLFW_KEY_Q,
			R				  = GLFW_KEY_R,
			S				  = GLFW_KEY_S,
			T				  = GLFW_KEY_T,
			U				  = GLFW_KEY_U,
			V				  = GLFW_KEY_V,
			W				  = GLFW_KEY_W,
			X				  = GLFW_KEY_X,
			Y				  = GLFW_KEY_Y,
			Z				  = GLFW_KEY_Z,
			Menu			  = GLFW_KEY_MENU,
			Numpad0			  = GLFW_KEY_KP_0,
			Numpad1			  = GLFW_KEY_KP_1,
			Numpad2			  = GLFW_KEY_KP_2,
			Numpad3			  = GLFW_KEY_KP_3,
			Numpad4			  = GLFW_KEY_KP_4,
			Numpad5			  = GLFW_KEY_KP_5,
			Numpad6			  = GLFW_KEY_KP_6,
			Numpad7			  = GLFW_KEY_KP_7,
			Numpad8			  = GLFW_KEY_KP_8,
			Numpad9			  = GLFW_KEY_KP_9,
			NumpadMultiply	  = GLFW_KEY_KP_MULTIPLY,
			NumpadAdd		  = GLFW_KEY_KP_ADD,
			NumpadSubtract	  = GLFW_KEY_KP_SUBTRACT,
			NumpadDecimal	  = GLFW_KEY_KP_DECIMAL,
			NumpadDivide	  = GLFW_KEY_KP_DIVIDE,
			F1				  = GLFW_KEY_F1,
			F2				  = GLFW_KEY_F2,
			F3				  = GLFW_KEY_F3,
			F4				  = GLFW_KEY_F4,
			F5				  = GLFW_KEY_F5,
			F6				  = GLFW_KEY_F6,
			F7				  = GLFW_KEY_F7,
			F8				  = GLFW_KEY_F8,
			F9				  = GLFW_KEY_F9,
			F10				  = GLFW_KEY_F10,
			F11				  = GLFW_KEY_F11,
			F12				  = GLFW_KEY_F12,
			NumLock			  = GLFW_KEY_NUM_LOCK,
			ScrollLock		  = GLFW_KEY_SCROLL_LOCK,
			LeftShift		  = GLFW_KEY_LEFT_SHIFT,
			RightShift		  = GLFW_KEY_RIGHT_SHIFT,
			RightControl	  = GLFW_KEY_RIGHT_CONTROL,
			RightAlt		  = GLFW_KEY_RIGHT_ALT,
			
			LocalSemicolon	  = GLFW_KEY_SEMICOLON, // ¨
			LocalPlus		  = GLFW_KEY_EQUAL,
			LocalComma		  = GLFW_KEY_COMMA,
			LocalMinus		  = GLFW_KEY_MINUS,
			LocalPeriod		  = GLFW_KEY_PERIOD,
			LocalSlash		  = GLFW_KEY_SLASH, // '
			LocalTilde		  = GLFW_KEY_GRAVE_ACCENT, // ö
			LocalOpenBracket  = GLFW_KEY_LEFT_BRACKET, // ´
			LocalBackslash	  = GLFW_KEY_BACKSLASH, // §
			LocalCloseBracket = GLFW_KEY_RIGHT_BRACKET, // å
			LocalQuote		  = GLFW_KEY_APOSTROPHE, // ä
			LocalAngleBracket = GLFW_KEY_WORLD_2,
			LeftSuper		  = GLFW_KEY_LEFT_SUPER,
			RightSuper		  = GLFW_KEY_RIGHT_SUPER,
			NumpadEnter		  = GLFW_KEY_KP_ENTER,
			COUNT			  = GLFW_KEY_LAST
		};
	}

}