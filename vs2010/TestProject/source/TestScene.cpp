#include "TestScene.hpp"

#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>
#include <UtH/Renderer/TextureAtlas.hpp>
#include <UtH/Core/Randomizer.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

const unsigned int sprites = 40;

TestScene::TestScene()
{}
TestScene::~TestScene()
{}

bool TestScene::Init()
{
	shader = new Shader();
	shader->LoadShader("Shaders/vertexshader.vert", "Shaders/fragmentshader.frag");
	shader->Use();
    uthEngine.GetWindow().SetViewport(umath::rectangle(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
    uthEngine.GetWindow().SetShader(shader);

	GameObject* temp;

#pragma region layers
	CreateLayer("monsu", 3);
	CreateLayer("derp", 1);
	CreateLayer("testi", 0);
#pragma endregion

#pragma region particles
    pSystem.AddAffector(new Affector([](Particle& particle, ParticleTemplate& pTemplate, float dt)

                                     {
                                         particle.transform.Move(particle.direction * dt);
                                         particle.transform.Rotate(50 * dt);
                                         particle.color.w = (pTemplate.lifetime - particle.lifetime.CurTime()) / pTemplate.lifetime;
                                     }));

	map = new TMX::Map("Maps/test.tmx");
	//map->transform.Move(-500, -300);
	map->transform.SetScale(0.2f, 0.2f);

    ParticleTemplate pTemplate;
    pTemplate.SetLifetime(2);
    pTemplate.SetSpeed(80, 150);
    pTemplate.SetTexture(&uthRS.LoadTexture("particle.tga"));
    pTemplate.SetInitFunction([](Particle& particle, ParticleTemplate& pTemplate)
    {
        particle.direction = umath::vector2(Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed), Randomizer::GetFloat(-30.f, 30.0f));
    });
    pSystem.SetTemplate(pTemplate);
    pSystem.transform.SetPosition(50.f, 0.f);
#pragma endregion

#pragma region rendertex
    rtex.Initialize(uthEngine.GetWindowResolution() / /*0.125f*/0.5f, false);
    rtex.SetCamera(&camera);
    rtex.SetShader(shader);
    rtex.SetViewport(umath::rectangle(0, 0, rtex.GetSize().x, rtex.GetSize().y));
	
    // render rtex
    rtexSprite = new GameObject();
    rtexSprite->AddComponent(new Sprite(&rtex.GetTexture(), "rtexSprite"));
    rtexSprite->transform.SetPosition(0, 0);
	rtexSprite->transform.SetScale(/*0.0625,0.0625*/0.5f,0.5f);
#pragma endregion

#pragma region textureatlas_spritebatch
    atlas.LoadFromFile("atlastest.xml");
    batch.SetTextureAtlas(&atlas);
    const float radius = 550.f;

    for (int i = 0; i < sprites; ++i)
    {
        GameObject* obj = new GameObject();
        batch.AddSprite(obj, i % 2 == 0 ? "flagYellow.png" : "bomb.png");
        obj->transform.SetPosition((radius * std::cos(i * (6.284f / static_cast<float>(sprites)))), (radius * std::sin(i * (6.284f / static_cast<float>(sprites)))));
    }

    AddGameObjectToLayer(1, &batch);
#pragma endregion


#pragma region box2d
	// Ground level
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, 5.0f);
	groundBody = world.CreateBody(&groundBodyDef);

	// Ground size
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 1.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	// smile object
	go = new GameObject();
	go->AddComponent(new Sprite("Maps/tmw_desert_spacing.tga"));
	go->transform.Move(-100, -400); // need to move it before rigidbody is added
	go->AddComponent(new Rigidbody(&world));
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);

	// other object
	go = new GameObject();
	go->AddComponent(new Sprite(umath::vector4(1, 0, 1, 1), umath::vector2(100, 100)));
	go->transform.Move(0, -200);
	go->AddComponent(new Rigidbody(&world));
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);

	// Ground visual
	go = new GameObject();
	go->AddComponent(new Sprite(umath::vector4(1, 1, 1, 1),
		umath::vector2(2000, 2*PIXELS_PER_METER)));
	go->transform.SetPosition(0, groundBody->GetPosition().y * PIXELS_PER_METER);
	gameObjects.push_back(go);
	AddGameObjectToLayer(0, go);
#pragma endregion

#pragma region animation
	go = new GameObject();
	go->AddComponent(new AnimatedSprite(&uthRS.LoadTexture("monsu.tga"), 5, 4, 4, 1.f, 0, false, true));
	((AnimatedSprite*)go->GetComponent("AnimatedSprite"))->ChangeAnimation(0, 4, 2, 3.0f, true, false);
	go->transform.SetScale(10,10);
	gameObjects.push_back(go);
	AddGameObjectToLayer(3, go);
#pragma endregion

	camera.SetSize(uthEngine.GetWindowResolution());
	camera.SetPosition(0, 0);

#pragma region text
	temp = go = new GameObject();
	auto text = new Text("8bitoperator.ttf", 32);
	go->AddComponent(text);
	text->AddText(L"!\"#$%&'()*+,-./0123456789:;<=     >?"
				  L"\n@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
				  L"\n`abcdefghijklmnopqrstuvwxyz{|}~", umath::vector4(0, 0, 0, 1));
	text->AddText(L"\nPrkl!", umath::vector4(1,0,0,1));
	go->transform.SetOrigin(uth::Origin::Point::TopLeft);
	go->transform.Move(-400, 200);
	gameObjects.push_back(go);
	AddGameObjectToLayer(1, go);
#pragma endregion


    obj = new GameObject();
    //obj->AddComponent(new Sprite("test.tga"));
    obj->AddComponent(new Sprite(umath::vector4(1, 1, 1, 1), umath::vector2(100,100)));
    obj->transform.SetPosition(0, 0);

	WriteLog("GameObjects: %d\n", gameObjects.size());
	WriteLog("Layers: %d\n", layers.size());

	//SetLayerActive(0, false);
	SetLayerActive(3, false);

	go = temp;
	return true;
}
bool TestScene::DeInit()
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
	delete rtexSprite;
	delete obj;
	delete map;

	return true;
}

bool TestScene::Update(float dt)
{
    static float count = 1.f;

    if ((count += dt) > 0.1f)
    {
        pSystem.Emit(5);

        count = 0.f;
    }

    const float offset = 75.f * dt;

	go->transform.SetPosition(uthInput.Common.Position()-uthEngine.GetWindowResolution()/2.f);
	int orig = 0;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad1))
		orig = 1;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad2))
		orig = 2;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad3))
		orig = 3;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad4))
		orig = 4;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad5))
		orig = 5;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad6))
		orig = 6;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad7))
		orig = 7;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad8))
		orig = 8;
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Key::Numpad9))
		orig = 9;
	if (orig != 0)
		go->transform.SetOrigin(orig);

    obj->transform.Rotate(offset*0.125);

    camera.Rotate(-offset);
    rtexSprite->transform.Rotate(offset);

	for(size_t i = 0; i < layers.size(); i++)
		layers.at(i)->Update(dt);


	const float timeStep = 1.f/60.f;
	world.Step(timeStep, 8, 3);

	//if(uthInput.Common == InputEvent::TAP)
	//{
	//	WriteLog("Tapped");
	//	uthSceneM.GoToScene(0);
	//}
	//if(uthInput.Common != InputEvent::NONE)
	//{
	//	WriteLog("Action");
	//	uthSceneM.GoToScene(0);
	//}

    pSystem.Update(dt);

	return true;
}
bool TestScene::Draw()
{
    //obj->Draw(uthEngine.GetWindow());
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);

    rtex.Clear(0, 0, 1, 1);
 	for(size_t i = 0; i < layers.size(); i++)
         layers.at(i)->Draw(rtex);

    rtex.Update();
    rtex.GetTexture();
    //static_cast<Sprite*>(rtexSprite->GetComponent("rtexSprite"))->SetTexture(&rtex.GetTexture());
    rtexSprite->Draw(uthEngine.GetWindow());
    pSystem.Draw(uthEngine.GetWindow());

	map->Draw(uthEngine.GetWindow());

	return true;
}