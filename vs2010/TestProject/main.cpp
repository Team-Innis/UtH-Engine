#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Core\Shader.hpp>
#include <iostream>
#include <Windows.h>
#include <UtH\Core\VertexBuffer.hpp>


int main(int* argc, char** argv)
{
    uth::WindowSettings settings;
	settings.contextVersionMajor = 2;
	settings.contextVersionMinor = 1;

    uthGraphics.createWindow(settings);

	uth::Shader shader;
	shader.LoadShader(uth::VERTEX_SHADER, "vertexshader.vert");
	shader.LoadShader(uth::FRAGMENT_SHADER, "fragmentshader.frag");
	shader.LinkShader();
	shader.Use();

	uth::VertexBuffer buf;
	buf.addVertex(umath::vector3(-0.5, -0.5, 0), umath::vector2(0.1f, 0.2f));
	buf.addVertex(umath::vector3(0.5, -0.5, 0), umath::vector2(0.3f, 0.4f));
	buf.addVertex(umath::vector3(0.5, 0.5, 0), umath::vector2(0.5f, 0.6f));
	buf.addVertex(umath::vector3(-0.5, 0.5, 0), umath::vector2(0.7f, 0.8f));
	buf.addIndex(0);
	buf.addIndex(1);
	buf.addIndex(2);
	buf.addIndex(1);
	buf.addIndex(3);
	buf.addIndex(2);

	buf.setVertices(&shader);

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
    {
        int number = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;

        uthGraphics.clear(number, number, number);
		buf.setVertices(&shader);

        uthGraphics.swapBuffers();
    }
	

    uthGraphics.destroyWindow();

	return 0;
}