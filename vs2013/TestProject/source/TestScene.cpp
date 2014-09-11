#include <TestScene.hpp>
#include <Scenes.hpp>

using namespace uth;


namespace
{
    enum Layers
    {
        Default,
        Other
    };
}

TestScene::TestScene()
    : ps(nullptr)
{}
TestScene::~TestScene()
{}

bool TestScene::Init()
{
	// Layers
    CreateLayer(Default);
    CreateLayer(Other);

    // Objects
    // First
	{
	    //auto test = new GameObject();
		//test->AddComponent(new Sprite(pmath::Vec4(1,0,0,1),pmath::Vec2(128,128)));
	    //AddGameObjectToLayer(Default, test);
    }

    // Second (ParticleSystem)
    {
        ParticleTemplate pt;
        pt.SetLifetime(1.f);
        pt.SetSpeed(10.f, 150.f);
        pt.SetTexture(uthRS.LoadTexture("particle.tga"));

        ps = new ParticleSystem(100);
        ps->SetTemplate(pt);

        Affector* aff = new Affector([](Particle& part, const ParticleTemplate& ptemp, float dt)
        {
            part.Move(part.direction * dt);
        });

        ps->AddAffector(aff);
        AddGameObjectToLayer(Other, ps);
    }

	return true;
}
bool TestScene::DeInit()
{
	return true;
}

bool TestScene::Update(float dt)
{
    if (uthInput.Mouse.IsButtonPressed(uth::Mouse::RIGHT))
    {
        RemoveGameObjectFromLayer(Other, ps);
        ps = nullptr;
    }

    if (ps)
        ps->Emit(1);
    
    UpdateLayers(dt, -1);

	return true;
}
bool TestScene::Draw()
{
	DrawLayers(uthEngine.GetWindow(), -1);

	return true;
}