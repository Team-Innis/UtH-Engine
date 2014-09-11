#include "TestScene.hpp"

#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Engine/Particles/ParticleTemplate.hpp>
#include <UtH/Engine/Particles/Affector.hpp>
#include <UtH/Platform/Input.hpp>


using namespace uth;

GameObject text;

TestScene::TestScene()
    : ps(100)
{}
TestScene::~TestScene()
{}

bool TestScene::Init()
{
	shader = new Shader();
	shader->LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
	shader->Use();
    uthEngine.GetWindow().SetViewport(pmath::Rect(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
    uthEngine.GetWindow().SetShader(shader);

	test = new GameObject();
	test->AddComponent(new Sprite(pmath::Vec4(1,0,0,1),pmath::Vec2(128,128)));

    ParticleTemplate pt;
    pt.SetLifetime(1.f);
    pt.SetSpeed(10.f, 150.f);
    pt.SetTexture(uthRS.LoadTexture("particle.tga"));

    ps.SetTemplate(pt);
    

    Affector* aff = new Affector([](Particle& part, const ParticleTemplate& ptemp, float dt)
    {
        part.Move(part.direction * dt);
    });
    
    ps.AddAffector(aff);

    text.AddComponent(new Text("8bitoperator.ttf", 16));
    text.transform.Move(-300, 0);


	

	return true;
}
bool TestScene::DeInit()
{
	return true;
}

bool TestScene::Update(float dt)
{
    ps.Emit(1);
    ps.Update(dt);
    auto t = text.GetComponent<Text>("Text");
    t->SetText("Buttons:\n");
    for (int i = 0; i < Controller::BUTTON_COUNT; ++i)
    {
        if (uthInput.Controller.IsButtonDown(static_cast<Controller::Button>(i)))
        {
            char temp[5];
            sprintf(temp, "%d\n", i);

            t->AddText(temp);
        }
    }



	if (uthInput.Touch.Motion() == TouchMotion::TAP)
	{ 
		WriteLog("TAP");
	}
	else if (uthInput.Touch.Motion() == TouchMotion::DRAG)
	{
		WriteLog("DRAG");
	}
	else if (uthInput.Touch.Motion() == TouchMotion::PINCH_IN)
	{
		WriteLog("PINCH IN");
	}
	else if (uthInput.Touch.Motion() == TouchMotion::PINCH_OUT)
	{
		WriteLog("PINCH OUT");
	}
	

	return true;
}
bool TestScene::Draw()
{
	test->Draw(uthEngine.GetWindow());
    ps.Draw(uthEngine.GetWindow());
    text.Draw(uthEngine.GetWindow());
	return true;
}