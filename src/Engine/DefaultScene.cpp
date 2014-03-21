#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>

#include <UtH\Platform\Debug.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	shader.LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader.Use();

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);


	//camera.SetViewport(umath::rectangle(0, 0, 1600, 900));
	camera.SetSize(Hood.GetWindowSize());
	camera.SetPosition(0, 0);
	//camera.SetZoom(0);
	//camera.SetRotation(180);

	gameObject.AddComponent(new Sprite("test.tga"));
	gameObject.AddComponent(new Rigidbody(&world));
	gameObject2.AddComponent(new Sprite(umath::vector4(1, 0, 1, 1), umath::vector2(100, 100)));
	gameObject2.AddComponent(new Rigidbody(&world));
	gameObject2.transform.Move(0, -200);

	gameObject3.AddComponent(new Sprite(umath::vector4(1, 1, 1, 1),
		umath::vector2(50 * PIXELS_PER_METER, 10 * PIXELS_PER_METER)));
	gameObject3.transform.SetPosition(0, -groundBody->GetPosition().y * PIXELS_PER_METER);
	//gameObject.transform.Move(100, 100);
	//auto sprite = (Sprite*)gameObject.GetComponent("Sprite");
	//sprite->SetColor(1, 0, 1, 1);
	//gameObject.transform.SetSize(0.5f, 0.5f);
	//gameObject.GetComponent("Sprite")->SetActive(false);
	//WriteLog("\nactive: %d", gameObject.transform.GetActive());

	CreateLayer("testi");
	AddGameObjectToLayer(0, &gameObject3);
	AddGameObjectToLayer(0, &gameObject);
	AddGameObjectToLayer(0, &gameObject2);
	//AddGameObjectToLayer("testi", &gameObject2);

	//gameObject.transform.SetPosition(0,0);
	//gameObject.transform.parent->transform.Rotate(30);
	//gameObject.transform.SetSize(2, 2);
	//gameObject.transform.SetActive(true);

	auto text = new Text("8bitoperator.ttf", 32);
	text->AddText(L"!\"#$%&'()*+,-./0123456789:;<=     >?"
				  L"\n@ABCDEFGHIJKLMNOPQRSTUVWXYZÖÄÅ[\\]^_"
				  L"\n`abcdefghijklmnopqrstuvwxyzöäå{|}~");

	text->AddText(L"\nPrkl!");

	textObject.AddComponent(text);
	textObject.transform.Move(-400, 200);
	AddGameObjectToLayer(0, &textObject);

	//layers.at(0)->transform.Rotate(90);
	//layers.at(0)->transform.Rotate(10);


	return true;
}
bool DefaultScene::DeInit()
{
	return true;
}

bool DefaultScene::Update(double dt)
{
	//layers.at(0)->transform.Rotate(0.01f);

	for(size_t i = 0; i < layers.size(); i++)
		layers.at(i)->Update(dt);

	//gameObject.transform.Move(0, 1.f * dt);

	static float timeStep = 1.f/60.f;
	//world.Step(timeStep, 8, 3);

	return true;
}
bool DefaultScene::Draw()
{
	//gameObject.Draw(&shader, &camera);
	//textObject.Draw(&shader, &camera);
	//gameObject.Draw(&shader);
	//gameObject2.Draw(&shader);
	
	for(size_t i = 0; i < layers.size(); i++)
		layers.at(i)->Draw(&shader, &camera);


	return true;
}
