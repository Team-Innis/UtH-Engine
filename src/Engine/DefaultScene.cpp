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
    shader->LoadShader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
    shader->Use();

    uthEngine.GetWindow().SetViewport(umath::rectangle(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
    uthEngine.GetWindow().SetShader(shader);
    WriteLog("x %f, y %f", uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y);
    rtex.Initialize(uthEngine.GetWindowResolution() / 2.f, false);
    rtex.SetCamera(&camera);
    rtex.SetShader(shader);
    rtex.SetViewport(umath::rectangle(0, 0, rtex.GetSize().x, rtex.GetSize().y));

    camera.SetSize(uthEngine.GetWindowResolution());
    camera.SetPosition(0, 0);



    obj = new GameObject();
    //obj->AddComponent(new Sprite("test.tga"));
    obj->AddComponent(new Sprite("engineLogo.tga"));
    obj->transform.SetPosition(0, 0);
	obj->transform.SetScale(0.5f);

    WriteLog("GameObjects: %d\n", gameObjects.size());
    WriteLog("Layers: %d\n", layers.size());

    return true;
}
bool DefaultScene::DeInit()
{
    delete obj;
	delete shader;

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
	if(uthInput.Common == InputEvent::TAP)
    {
        /*DeInit();
        Init();*/
		WriteLog("Tapped %d\n", uthInput.Common.Event());
        uthSceneM.GoToScene(0);
    }

    return true;
}
bool DefaultScene::Draw()
{
	uthEngine.GetWindow().Clear(0,0,0,1);
    obj->Draw(uthEngine.GetWindow());


    return true;
}