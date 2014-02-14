#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include <UtH\Resources\ResourceManager.h>
//#include <UtH\Resources\ResourceManager.h>
#include <UtH\Audio\Audio.h>

int main()
{
    uth::WindowSettings settings;

    uthGraphics.createWindow(settings);

	//uth::Audio* audio = new uth::Audio();

	//audio->Load("testi3.wav");
	//audio->Play();
	//audio->Loop(true);

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
    {
        int number = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;

        uthGraphics.clear(number, number, number);
        uthGraphics.swapBuffers();
    }


    uthGraphics.destroyWindow();

	return 0;
}