#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Renderer/SpriteBatch.hpp>
#include <UtH\Platform\Input.hpp>

#include <UtH/Platform/HiResTimer.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

const unsigned int sprites = 3000;

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
    shader.LoadShader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
	shader.Use();

    atlas.LoadFromFile("atlastest.tga");

	//camera.SetViewport(umath::rectangle(0, 0, 1600, 900));
    camera.SetSize(1600, 800).SetPosition(0, 0);
	//camera.SetZoom(0);
	//camera.SetRotation(45);

    obj.AddComponent(new Sprite("test.tga"));
	//gameObject.transform.SetSize(0.5f, 0.5f);
	//gameObject.transform.SetPosition(-0.5f, -0.5f);
	//gameObject.transform.parent->transform.Rotate(0);
	//gameObject.transform.SetSize(100, 100);
    WriteLog("markA");
    bShader.LoadShader("Shaders/batchvertexshader.vert", "Shaders/batchfragmentshader.frag");
    
    WriteLog("mark");
    bShader.Use();

    batch.SetTextureAtlas(&atlas);

    for (int i = 0; i < sprites; ++i)
    {
        WriteLog("%d ",i);
        std::cout << std::endl;
        objects.push_back(new GameObject());

        objects.back()->transform.SetPosition(100 + (10 * i), 100 + (10 * i));
        //objects.back()->transform.SetRotation(180.f);

        batch.AddSprite(objects.back(), umath::vector2(129.f, 71.f), "cloud3.png");
    }

	return true;
}
bool DefaultScene::DeInit()
{
	return true;
}

bool DefaultScene::Update(double dt)
{
    //camera.Rotate(10.f * dt);
    //obj.transform.Rotate(10.f * dt);
    //obj.transform.Move(10.f * dt, 10.f * dt);

    //for (int i = 0; i < sprites; ++i)
    //{
    //    objects[i]->transform.SetPosition(UTHInput.Mouse.MousePosition());
    //}





	return true;
}
bool DefaultScene::Draw()
{
    shader.Use();
	shader.SetUniform("unifProjection", camera.GetProjectionTransform());
    bShader.Use();
    bShader.SetUniform("unifProjection", camera.GetProjectionTransform());
	//gameObject.Draw(&shader);
    Timer timer;
    shader.Use();
    for (int i = 0; i < sprites; ++i)
    {
        obj.Draw(&shader, &camera);
    }
    WriteLog("%f    ",1/timer.UpdateDeltaTime());
    bShader.Use();
    batch.Draw(&bShader);
    WriteLog("%f\n",1/timer.UpdateDeltaTime());

	return true;
}
