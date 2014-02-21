#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Core\Shader.hpp>
#include <iostream>
#include <Windows.h>
#include <UtH\Core\VertexBuffer.hpp>

#pragma comment(lib, "glfw3d.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "Audio.lib")
#pragma comment(lib, "Core.lib")
#pragma comment(lib, "Engine.lib")
#pragma comment(lib, "Platform.lib")
#pragma comment(lib, "Renderer.lib")
#pragma comment(lib, "Resources.lib")
#pragma comment(lib, "UMath.lib")


int main(int* argc, char** argv)
{
    uth::WindowSettings settings;

    uthGraphics.createWindow(settings);

	uth::Shader shader;
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	/*uth::VertexBuffer buf;
	buf.addVertex(umath::vector3(-0.5, -0.5, 0), umath::vector2(0.1f, 0.2f));
	buf.addVertex(umath::vector3(0.5, -0.5, 0), umath::vector2(0.3f, 0.4f));
	buf.addVertex(umath::vector3(-0.5, 0.5, 0), umath::vector2(0.5f, 0.6f));
	buf.addVertex(umath::vector3(0.5, 0.5, 0), umath::vector2(0.7f, 0.8f));
	buf.addIndex(0);
	buf.addIndex(1);
	buf.addIndex(2);
	buf.addIndex(1);
	buf.addIndex(3);
	buf.addIndex(2);

	buf.setVertices(&shader);*/

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
    {
        int number = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;

        uthGraphics.clear(number, number, number);
		//buf.setVertices(&shader);

        uthGraphics.swapBuffers();
    }
	

    uthGraphics.destroyWindow();

	return 0;
}