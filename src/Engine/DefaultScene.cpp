#include <UtH/Engine/DefaultScene.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>
#include <UtH/Renderer/TextureAtlas.hpp>
#include <UtH/Engine/Text.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	
	WriteLog("DefaultScene Init");
	shader = new Shader();
	WriteLog("new shader");
	shader->LoadShader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
	WriteLog("Load Shader");
	shader->Use();

    uthEngine.GetWindow().SetViewport(umath::rectangle(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
	WriteLog("Window ViewPort");
    uthEngine.GetWindow().SetShader(shader);
	WriteLog("Window Shader");
    rtex.Initialize(uthEngine.GetWindowResolution() / 2.f, false);
    rtex.SetCamera(&camera);
    rtex.SetShader(shader);
    rtex.SetViewport(umath::rectangle(0, 0, rtex.GetSize().x, rtex.GetSize().y));

	camera.SetSize(uthEngine.GetWindowResolution());
	camera.SetPosition(0, 0);

	

    obj = new GameObject();
    //obj->AddComponent(new Sprite("test.tga"));
    //obj->AddComponent(new Sprite(umath::vector4(1, 1, 1, 1), umath::vector2(100,100)));
    auto text = new Text("8bitoperator.ttf", 30);
    obj->AddComponent(text);
    text->AddText(L"Testi 123");
    obj->transform.SetPosition(0, 0);

	WriteLog("GameObjects: %d\n", gameObjects.size());
	WriteLog("Layers: %d\n", layers.size());

	return true;
}
bool DefaultScene::DeInit()
{
	delete obj;
	return true;
}

bool DefaultScene::Update(float dt)
{
    /*const float offset = 75.f * dt;

    camera.Rotate(-offset);
    rtexSprite->transform.Rotate(offset);

	for(size_t i = 0; i < layers.size(); i++)
		layers.at(i)->Update(dt);

	const float timeStep = 1.f/60.f;
	world.Step(timeStep, 8, 3);
	*/
	if(uthInput.Mouse.IsButtonPressed(Mouse::MS1))
	{
		/*DeInit();
		Init();*/

		uthSceneM.GoToScene(0);
	}

	return true;
}
bool DefaultScene::Draw()
{
    obj->Draw(uthEngine.GetWindow());


	return true;
}
