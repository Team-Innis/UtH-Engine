#include <TestScene.hpp>
#include <Scenes.hpp>
#include <uth/Platform/JavaFunctions.hpp>

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
		AddChild(testParent = new GameObject());
		testSharedPtr = testParent->AddChild(testObject = new GameObject());
		testObject->AddComponent(new Sprite(pmath::Vec4(1, 0, 0, 1), pmath::Vec2(128, 128)));
    }

    // Second (ParticleSystem)
    {
        ParticleTemplate pt;
        pt.SetLifetime(-1.f);
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

	return true;
}
bool TestScene::DeInit()
{
	return true;
}

void TestScene::Update(float dt)
{
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::Q))
	{
		testParent->ExtractChild(testObject);
	}
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::W))
	{
		testParent->AddChild(testSharedPtr);
	}
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::E))
	{
		testParent->ExtractChild(testObject,true);
	}
	if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::R))
	{
		testParent->AddChild(testSharedPtr,true);
	}
	if (uthInput.Mouse.IsButtonDown(Mouse::MS1))
	{
		testObject->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
	}
	if (uthInput.Mouse.IsButtonDown(Mouse::MS2))
	{
		testParent->transform.SetPosition(uthEngine.GetWindow().PixelToCoords(uthInput.Mouse.Position()));
	}

	Scene::Update(dt);
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
