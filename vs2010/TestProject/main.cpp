#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Core\Shader.hpp>
#include <iostream>
#include <Windows.h>
#include <UtH\Core\VertexBuffer.hpp>
#include <UtH\Renderer\Texture.hpp>

#include <UtH\Engine\UtHEngine.h>

#include <UtH\Engine\GameObject.hpp>
#include <UtH\Engine\Sprite.hpp>

int main(int* argc, char** argv)
{
	//return Hood.AutoMainLoop();

    uth::WindowSettings settings;
	settings.contextVersionMajor = 2;
	settings.contextVersionMinor = 1;

    uthGraphics.createWindow(settings);

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

        uthGraphics.clear(number, number, number);
		gameObject.Draw(&shader);

        uthGraphics.swapBuffers();
    }
	

    uthGraphics.destroyWindow();

	return 0;
}