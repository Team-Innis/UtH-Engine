#include "UtH/Engine/Scene.hpp"

using namespace uth;

Scene::Scene()
{}
Scene::~Scene()
{}

bool Scene::Init()
{
	settings = new uth::WindowSettings();
	settings->contextVersionMajor = 2;
	settings->contextVersionMinor = 1;
    uthGraphics.createWindow(*settings);

	shader = new uth::Shader();
	shader->LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader->Use();
	
	buf = new uth::VertexBuffer();
	buf->addVertex(umath::vector3(-0.5, -0.5, 0), umath::vector2(0.0f, 0.0f)); // vasen alakulma
	buf->addVertex(umath::vector3(0.5, -0.5, 0), umath::vector2(1.0f, 0.0f)); // oikea alakulma
	buf->addVertex(umath::vector3(-0.5, 0.5, 0), umath::vector2(0.0f, 1.0f)); // vasen yläkulma
	buf->addVertex(umath::vector3(0.5, 0.5, 0), umath::vector2(1.0f, 1.0f)); // oikea yläkulma
	buf->addIndex(0);
	buf->addIndex(1);
	buf->addIndex(2);
	buf->addIndex(1);
	buf->addIndex(3);
	buf->addIndex(2);
	
	tex = new uth::Texture();
	tex->loadFromFile("test.tga");
	tex->bind();
	shader->SetUniform("unifSampler", 0);
	return true;
}
bool Scene::DeInit()
{
    uthGraphics.destroyWindow();
	return true;
}

bool Scene::Update(double dt)
{
	number = (GetAsyncKeyState(VK_SPACE) & 0x8000) ? 1 : 0;
	return true;
}
bool Scene::Draw()
{
    uthGraphics.clear(number, number, number);
	tex->bind();
    shader->SetUniform("unifSampler", 0);
	buf->draw(shader);

    uthGraphics.swapBuffers();
	return true;
}
