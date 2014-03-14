#include "UtH/Engine/DefaultScene.hpp"
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Renderer/SpriteBatch.hpp>
#include <UtH\Platform\Input.hpp>

using namespace uth;

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

    bShader.LoadShader("Shaders/batchvertexshader.vert", "Shaders/batchfragmentshader.frag");
    bShader.Use();

    batch.SetTextureAtlas(&atlas);

    for (int i = 0; i < 10; ++i)
    {
        objects.push_back(new GameObject());

        objects.back()->transform.SetPosition(100 + (10 * i), 100 + (10 * i));
        objects.back()->transform.SetRotation(180.f);

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
    obj.transform.Rotate(10.f * dt);
    obj.transform.Move(10.f * dt, 10.f * dt);



	return true;
}
bool DefaultScene::Draw()
{
    shader.Use();
	shader.SetUniform("unifProjection", camera.GetProjectionTransform());
    bShader.Use();
    bShader.SetUniform("unifProjection", camera.GetProjectionTransform());
	//gameObject.Draw(&shader);
    bShader.Use();
    batch.Draw(&bShader);
    shader.Use();
    obj.Draw(&shader);
	return true;
}
