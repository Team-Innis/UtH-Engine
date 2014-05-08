#include <UtH/Engine/DefaultScene.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>
#include <UtH/Renderer/TextureAtlas.hpp>
#include <UtH/Platform/Configuration.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
    shader = new Shader();
    shader->LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
    shader->Use();

    uthEngine.GetWindow().SetViewport(umath::rectangle(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
    uthEngine.GetWindow().SetShader(shader);
    WriteLog("Window Resolution %f x %f\n", uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y);

	logo = new GameObject();
	Text* text = new Text("kenpixel.ttf",32.f,"logotext");
	logo->AddComponent(text);
	text->AddText(L"UtH Engine");

	logo->transform.SetOrigin(5);

	totalTime = 0.f;

    return true;
}
bool DefaultScene::DeInit()
{
    delete logo;
	delete shader;

    return true;
}

bool DefaultScene::Update(float dt)
{
	totalTime += dt;
	if(totalTime >= 1.0f)
		uthSceneM.GoToScene(0);
    return true;
}

bool DefaultScene::Draw()
{
    logo->Draw(uthEngine.GetWindow());


    return true;
}