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
{}
TestScene::~TestScene()
{}

bool TestScene::Init()
{
    // Objects
    // First
	{
	    auto test = AddChild<GameObject>();
		test->AddComponent(new Sprite(pmath::Vec4(1,0,0,1),pmath::Vec2(128,128)));
    }

    // Second (ParticleSystem)
    {
        ParticleTemplate pt;
        pt.SetLifetime(1.f);
        pt.SetSpeed(10.f, 150.f);
        pt.SetTexture(uthRS.LoadTexture("particle.tga"));

        auto ps = AddChild(new ParticleSystem(100));
        ps->SetTemplate(pt);

        Affector* aff = new Affector();
        aff->SetParticleInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
        {
            pmath::Vec2 tvec(Randomizer::InsideCircle());
            tvec /= static_cast<float>(tvec.length());
            particle.direction = Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed) * tvec;
        });

        aff->SetParticleUpdateFunc([](Particle& part, const ParticleTemplate& ptemp, float dt)
        {
            part.Move(part.direction * dt);
        });

        ps->AddAffector(aff);
        ps->SetEmitProperties(true, 0.05f, 0.1f, 1, 5);
    }
	auto a = new TMX::Map("Maps/desert.tmx");
	a->AddTag("map");
	a->transform.SetScale(3.0f);
	AddChild(a);

	return true;
}
bool TestScene::DeInit()
{
	return true;
}

void TestScene::Update(float dt)
{
	if (Children("map").size() > 0)
		TestScene::Children("map")[0]->transform.SetPosition(uthEngine.GetWindow().pixelToCoords(uthInput.Common.Position()));
	uthEngine.GetWindow().GetCamera().SetPosition(pmath::Vec2(120,300));
	Scene::Update(dt);
}

//bool TestScene::Update(float dt)
//{
//    if (uthInput.Mouse.IsButtonPressed(uth::Mouse::RIGHT))
//        GetLayer(Other)->SetActive(false);
//    
//    UpdateLayers(dt, -1);
//
//	return true;
//}
//bool TestScene::Draw()
//{
//	DrawLayers(uthEngine.GetWindow(), -1);
//	return true;
//}