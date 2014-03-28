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
	switch(uthInput.Touch[0].Motion())
	{
	case  TouchMotion::TAP:
		WriteLog("Tapped!");
		break;
	case  TouchMotion::DRAG:
		WriteLog("DRAGGED!");
		break;
	}
	switch(uthInput.Touch[1].Motion())
	{
	case  TouchMotion::TAP:
		WriteLog("Tapped!1");
		break;
	case  TouchMotion::DRAG:
		WriteLog("DRAGGED!1");
		break;
	}
	switch(uthInput.Touch[2].Motion())
	{
	case  TouchMotion::TAP:
		WriteLog("Tapped!2");
		break;
	case  TouchMotion::DRAG:
		WriteLog("DRAGGED!2");
		break;
	}

	return true;
}

bool DefaultScene::Draw()
{
	shader.SetUniform("unifProjection", camera.GetProjectionTransform());
	gameObject.Draw(&shader);

	return true;
}
