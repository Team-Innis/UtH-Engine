#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>

#include <UtH\Platform\Debug.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	shader = new Shader();
	shader->LoadShader("vertexshader.vert", "fragmentshader.frag");
	shader->Use();

	// Ground level
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 5.0f);
	groundBody = world.CreateBody(&groundBodyDef);

	// Ground size
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 1.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	camera.SetSize(Hood.GetWindowSize());
	camera.SetPosition(0, 0);


	CreateLayer("testi", 1);
	CreateLayer("prkl", 0);
	CreateLayer("monsu", 3);
	GameObject* go = new GameObject();

	Texture* texture = new Texture();
	texture->LoadFromFile("test.tga");

	go->AddComponent(new Sprite(texture));
	go->AddComponent(new Rigidbody(&world));
	go->transform.Move(-100, -400);
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);

	texture = new Texture();
	texture->LoadFromFile("monsu.tga");

	//AnimatedSprite* as = new AnimatedSprite(texture, 5, 4, 4, 1.f, 0, false, true);
	//as->ChangeAnimation(4, 4, 6, 1.f);

	go = new GameObject();
	go->AddComponent(new AnimatedSprite(texture, 5, 4, 4, 1.f, 0, false, true));

	//((AnimatedSprite*)go->GetComponent("AnimatedSprite"))->ChangeAnimation(5, 4);

	//go->GetComponent("AnimatedSprite")

	gameObjects.push_back(go);
	AddGameObjectToLayer(3, go);

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
				  L"\n`abcdefghijklmnopqrstuvwxyzöäå{|}~");
	text->AddText(L"\nPrkl!");
	go->AddComponent(text);
	go->transform.Move(-400, 200);
	gameObjects.push_back(go);
	AddGameObjectToLayer(1, go);

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

bool DefaultScene::Update(double dt)
{
	//layers.at(0)->transform.Rotate(0.01f);

	for(size_t i = 0; i < layers.size(); i++)
		layers.at(i)->Update(dt);

	//gameObject.transform.Move(0, 1.f * dt);

	static float timeStep = 1.f/60.f;
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
		layers.at(i)->Draw(shader, &camera);

	return true;
}
