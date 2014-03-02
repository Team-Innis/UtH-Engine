#include <UtH/Platform/Input.hpp>

using namespace uth;

Input::Input()
{}
Input::~Input()
{}
void Input::SetWindow(void *windowHandle)
{
	m_windowHandle = windowHandle;
}
void Input::Update()
{
	Mouse.Update(m_windowHandle);
}
