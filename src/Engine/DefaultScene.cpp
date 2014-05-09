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

    logo = new GameObject();
    logo->AddComponent(new Sprite("eLogo.tga"));
    logo->transform.SetPosition(0, 0);
	logo->transform.SetScale(0.5f);

	totalTime = 0;

    return true;
}
bool DefaultScene::DeInit()
{
    delete logo;

    return true;
}

bool DefaultScene::Update(float dt)
{
	totalTime += dt;
	if(totalTime >= 2.0f)
    {
        uthSceneM.GoToScene(0);
	}
    return true;
}
bool DefaultScene::Draw()
{
	uthEngine.GetWindow().Clear(0,0,0,1);
    logo->Draw(uthEngine.GetWindow());


    return true;
}