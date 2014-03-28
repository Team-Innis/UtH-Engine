#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	camera.SetSize(1600, 900);
	camera.SetPosition(0, 0);

	gameObject.AddComponent(new uth::Sprite("test.tga"));

	m_zoom = 1.f;

	return true;
}
bool DefaultScene::DeInit()
{
	return true;
}

bool DefaultScene::Update(double dt)
{
	if(uthInput.Touch.Motion() == TouchMotion::TAP)
	{
		WriteLog("Tapped!");
	}

	return true;
}

bool DefaultScene::Draw()
{
	shader.SetUniform("unifProjection", camera.GetProjectionTransform());
	gameObject.Draw(&shader);

	return true;
}
