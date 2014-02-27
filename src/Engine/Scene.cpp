#include "UtH/Engine/Scene.hpp"

#include <UtH\Engine\Sprite.hpp>

using namespace uth;

Scene::Scene()
{}
Scene::~Scene()
{}

bool Scene::Init()
{
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	gameObject.AddComponent(new uth::Sprite("test.tga"));
	gameObject.transform.SetSize(0.5f, 0.5f);
	gameObject.transform.SetPosition(-0.5f, -0.5f);
	gameObject.transform.parent->transform.Rotate(45);

	return true;
}
bool Scene::DeInit()
{
	return true;
}

bool Scene::Update(double dt)
{
	return true;
}
bool Scene::Draw()
{
	gameObject.Draw(&shader);
	return true;
}
