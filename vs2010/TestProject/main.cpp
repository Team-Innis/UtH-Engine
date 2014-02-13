#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Core\Shader.hpp>
#include <iostream>
#include <Windows.h>
#include <UtH\Core\VertexBuffer.hpp>


int main(int* argc, char** argv)
{
    uth::WindowSettings settings;

    uthGraphics.createWindow(settings);

	uth::Shader shader;
	shader.LoadShader(uth::VERTEX_SHADER, "vertexshader.vert");
	shader.LoadShader(uth::FRAGMENT_SHADER, "fragmentshader.frag");
	shader.LinkShader();
	shader.Use();

	uth::VertexBuffer buf;
	buf.addVertex(umath::vector3(1, 1, 1), umath::vector2(0.1f, 0.1f));
	buf.setVertices(&shader);

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
    {
        int number = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;

        uthGraphics.clear(number, number, number);
        uthGraphics.swapBuffers();
    }
	

    uthGraphics.destroyWindow();

	return 0;
}