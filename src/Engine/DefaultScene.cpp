#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	shader = new Shader();
	shader->LoadShader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
	shader->Use();

    uthEngine.GetWindow().SetShader(shader);

	// Ground level
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 5.0f);
	groundBody = world.CreateBody(&groundBodyDef);

	// Ground size
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 1.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	camera.SetSize(uthEngine.GetWindowResolution());
	camera.SetPosition(0, 0);


	CreateLayer("testi", 0);
	GameObject* go = new GameObject();

	go->AddComponent(new Sprite("test.tga"));
	go->AddComponent(new Rigidbody(&world));
	go->transform.Move(-100, -400);
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);

	go = new GameObject();
	go->AddComponent(new Sprite(umath::vector4(1, 0, 1, 1), umath::vector2(100, 100)));
	go->AddComponent(new Rigidbody(&world));
	go->transform.Move(0, -200);
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);

	go = new GameObject();
	go->AddComponent(new Sprite(umath::vector4(1, 1, 1, 1),
		umath::vector2(2000, 2*PIXELS_PER_METER)));
	go->transform.SetPosition(0, groundBody->GetPosition().y * PIXELS_PER_METER);
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);

	go = new GameObject();
	auto text = new Text("8bitoperator.ttf", 32);
	text->AddText(L"!\"#$%&'()*+,-./0123456789:;<=     >?"
				  L"\n@ABCDEFGHIJKLMNOPQRSTUVWXYZÖÄÅ[\\]^_"
				  L"\n`abcdefghijklmnopqrstuvwxyzöäå{|}~", umath::vector4(0, 0, 0, 1));
	text->AddText(L"\nPrkl!");
	go->AddComponent(text);
	go->transform.Move(-400, 200);
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);

	WriteLog("GameObjects: %d\n", gameObjects.size());
	WriteLog("Layers: %d\n", layers.size());

	return true;
}
bool DefaultScene::DeInit()
{
	for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		delete (*it);
	}
	gameObjects.clear();


	for(auto it = layers.begin(); it != layers.end(); ++it)
	{
		delete (*it);
	}
	layers.clear();
	layersCount = 0;

	delete shader;

	return true;
}

bool DefaultScene::Update(float dt)
{
	//layers.at(0)->transform.Rotate(0.1f);

	for(size_t i = 0; i < layers.size(); i++)
		layers.at(i)->Update(dt);

	/*if(timer.GetCurTime() > 1.0f)
	{
		auto rigidBody = static_cast<Rigidbody*>(gameObjects.at(0)->GetComponent("Rigidbody"));
		rigidBody->ApplyImpulse(umath::vector2(50, 0), umath::vector2(-64, 64));
		timer.Reset();
		WriteLog("Impulse!\n");
	}*/

	auto rigidBody = static_cast<Rigidbody*>(gameObjects.at(0)->GetComponent("Rigidbody"));

	const int speed = 5;


	if(GetAsyncKeyState(VK_LEFT))
	{
		umath::vector2 curV = rigidBody->GetVelocity();
		rigidBody->SetVelocity(umath::vector2(-speed, curV.y));
	}

	if(GetAsyncKeyState(VK_RIGHT))
	{
		umath::vector2 curV = rigidBody->GetVelocity();
		rigidBody->SetVelocity(umath::vector2(speed, curV.y));
	}

	if(GetAsyncKeyState(VK_UP))
	{
		umath::vector2 curV = rigidBody->GetVelocity();
		rigidBody->SetVelocity(umath::vector2(curV.x, -speed));
	}
	if(GetAsyncKeyState(VK_DOWN))
	{
		umath::vector2 curV = rigidBody->GetVelocity();
		rigidBody->SetVelocity(umath::vector2(curV.x, speed));
	}


	const float timeStep = 1.f/60.f;
	world.Step(timeStep, 8, 3);

	if(UTHInput.Mouse.IsButtonPressed(Mouse::MS1))
	{
		DeInit();
		Init();
	}

	return true;
}
bool DefaultScene::Draw()
{	
	for(size_t i = 0; i < layers.size(); i++)
        layers.at(i)->Draw(uthEngine.GetWindow());

	return true;
}
