#include <iostream>
#include <Windows.h>

#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Core\Shader.hpp>
#include <UtH\Core\VertexBuffer.hpp>
#include <UtH\Renderer\Texture.hpp>
#include <UtH\Platform\Window.hpp>
#include <UtH\Engine\GameObject.hpp>
#include <UtH\Engine\Sprite.hpp>
#include <UtH\Engine\UtHEngine.h>
#include <UtH\Audio\Audio.h>


int main()
{
	//return Hood.AutoMainLoop();

    uth::WindowSettings settings;
    settings.size = umath::vector2(1600, 900);
    settings.position = umath::vector2(8, 30);
	settings.contextVersionMajor = 3;
	settings.contextVersionMinor = 1;
    settings.fullScreen = false;


    uth::Window wndw(settings);
	uthGraphics.setBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);

	uth::FileReader::isCompressed = true;

	uth::Shader shader;
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	uth::GameObject gameObject;
	gameObject.AddComponent(new uth::Sprite("test.tga"));

	gameObject.transform.SetSize(0.5f, 0.5f);
	gameObject.transform.SetPosition(-0.5f, -0.5f);
	gameObject.transform.parent->transform.Rotate(45);

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
    {
        int number = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;

        wndw.clear(number, number, number);
		gameObject.Draw(&shader);

        wndw.swapBuffers();
    }
	

    wndw.destroy();

	return 0;
}