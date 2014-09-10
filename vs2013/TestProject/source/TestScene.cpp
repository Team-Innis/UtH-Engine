#include "TestScene.hpp"

#include <UtH/uthEngine.hpp>

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

	test = new GameObject();
	test->AddComponent(new Sprite(pmath::Vec4(1,0,0,1),pmath::Vec2(128,128)));

    ParticleTemplate pt;
    pt.SetLifetime(1.f);
    pt.SetSpeed(10.f, 150.f);
    pt.SetTexture(uthRS.LoadTexture("particle.tga"));

    ps.SetTemplate(pt);
    

    Affector aff([](Particle& part, const ParticleTemplate& ptemp, float dt)
    {
        part.Move(part.direction * dt);
    });
    
    ps.AddAffector(aff);

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

	return true;
}
bool TestScene::Draw()
{
	test->Draw(uthEngine.GetWindow());
    ps.Draw(uthEngine.GetWindow());
	return true;
}