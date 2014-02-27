#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	gameObject.AddComponent(new uth::Sprite("test.tga"));
	gameObject.transform.SetSize(0.5f, 0.5f);
	gameObject.transform.SetPosition(-0.5f, -0.5f);
	gameObject.transform.parent->transform.Rotate(45);

	return true;
}
bool DefaultScene::DeInit()
{
	return true;
}

bool DefaultScene::Update(double dt)
{
	return true;
}
bool DefaultScene::Draw()
{
	gameObject.Draw(&shader);
	return true;
}
