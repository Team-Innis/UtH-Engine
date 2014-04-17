#include <UtH/Platform/Android/InputKeyboard.hpp>
#include <UtH/Platform/Debug.hpp>

namespace uth
{
	KeyboardInput::KeyboardInput()
	{}
	KeyboardInput::~KeyboardInput()
	{}
		
	void KeyboardInput::Initiate()
	{}
	void KeyboardInput::Update()
	{}

	bool KeyboardInput::IsKeyDown(Keyboard::Key)
	{
		WriteLog("No Keyboard with android. Returning false");
		return false;
	}
	bool KeyboardInput::IsKeyPressed(Keyboard::Key)
	{
		WriteLog("No Keyboard with android. Returning false");
		return false;
	}
	bool KeyboardInput::IsKeyReleased(Keyboard::Key)
	{
		WriteLog("No Keyboard with android. Returning false");
		return false;
	}
}