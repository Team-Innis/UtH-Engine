#include <UtH\Math\Math.hpp>
#include <UtH\Platform\Graphics.hpp>
#include <UtH\Core\Shader.hpp>
#include <iostream>
#include <Windows.h>
#include <UtH\Core\VertexBuffer.hpp>
#include <UtH\Renderer\Texture.hpp>
#include <UtH\Platform\Window.hpp>

int main()
{
    uth::WindowSettings settings;
    settings.size = umath::vector2(1600, 900);
    settings.position = umath::vector2(8, 30);
	settings.contextVersionMajor = 3;
	settings.contextVersionMinor = 1;
    settings.fullScreen = false;

    uth::Window wndw(settings);
	uthGraphics.setBlendFunction(true, uth::SRC_ALPHA, uth::ONE_MINUS_SRC_ALPHA);

	uth::Shader shader;
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	uth::VertexBuffer buf;
	buf.addVertex(umath::vector3(-0.5, -0.5, 0), umath::vector2(0.0f, 0.0f)); // vasen alakulma
	buf.addVertex(umath::vector3(0.5, -0.5, 0), umath::vector2(1.0f, 0.0f)); // oikea alakulma
	buf.addVertex(umath::vector3(-0.5, 0.5, 0), umath::vector2(0.0f, 1.0f)); // vasen yläkulma
	buf.addVertex(umath::vector3(0.5, 0.5, 0), umath::vector2(1.0f, 1.0f)); // oikea yläkulma
	buf.addIndex(0);
	buf.addIndex(1);
	buf.addIndex(2);
	buf.addIndex(1);
	buf.addIndex(3);
	buf.addIndex(2);

	uth::Texture tex, tex2;
	tex.loadFromFile("test.tga");
	tex.bind();
	shader.SetUniform("unifSampler", 0);

	tex2.loadFromFile("test2.tga");

	buf.setVertices(&shader);

    while(!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
    {
        int number = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;

        wndw.clear(number, number, number);

		if(GetAsyncKeyState(VK_RETURN))
			tex2.bind();
		else
			tex.bind();

     	shader.SetUniform("unifSampler", -2);
		buf.setVertices(&shader);

        wndw.swapBuffers();
    }
	

    wndw.destroy();

	return 0;
}