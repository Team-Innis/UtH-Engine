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

const unsigned int sprites = 40;

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
    uthEngine.GetWindow().GetCamera().Scroll(0, -200);

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

	//music = Sound::Load("media/music.ogg");
	//music->Play();
	//music->Loop(true);

	

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

    if (uthInput.Mouse.IsButtonDown(uth::Mouse::LEFT))
    {
        auto pix = uthInput.Mouse.Position();
        auto vec1 = uthEngine.GetWindow().pixelToCoords(pix);
        auto vec2 = uthEngine.GetWindow().coordsToPixel(vec1);
        std::cout << pix.x << ", " << pix.y << "; " << vec1.x << ", " << vec1.y << "; " << vec2.x << ", " << vec2.y << std::endl;
    }

	return true;
}
bool TestScene::Draw()
{
	test->Draw(uthEngine.GetWindow());
    ps.Draw(uthEngine.GetWindow());
	return true;
}