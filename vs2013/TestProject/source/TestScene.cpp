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
    : textObject(nullptr)
{
    uthSceneM.RegisterSaveable<TestScene>();
}
TestScene::~TestScene()
{}

void setAffectors(ParticleSystem* ps)
{
    ps->Clear(false, true);

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
}

bool TestScene::Init()
{
    return true;

    // Objects
    // First
	{
	    auto test = AddChild<GameObject>();
		test->AddComponent(new Sprite(pmath::Vec4(1,0,0,1),pmath::Vec2(128,128)));
    }

    // Second (ParticleSystem)
    {
        ParticleTemplate pt;
        pt.SetLifetime(-1.f);
        pt.SetSpeed(10.f, 150.f);
        pt.SetTexture(uthRS.LoadTexture("particle.tga"));

        auto ps = AddChild(new ParticleSystem(100));
        ps->AddTag("PS");
        ps->SetTemplate(pt);

        setAffectors(ps.get());
        ps->SetEmitProperties(true, 0.05f, 0.1f, 1, 5);
    }

    GameObject* to = AddChild(new GameObject()).get();
    to->AddComponent(new Text("FreePixel.ttf", 32))->SetText(L"QWERTYUIOPASDFGHJKLZXCVBNM;:_");

	return true;
}
bool TestScene::DeInit()
{
    //uthSceneM.SaveCurrentScene("test");
	return true;
}

void TestScene::Update(float dt)
{
	Scene::Update(dt);

    if (textObject)
    {
        textObject->transform.Move((uthInput.Keyboard.IsKeyDown(uth::Keyboard::Right) - uthInput.Keyboard.IsKeyDown(uth::Keyboard::Left)) * 100.f * dt,
                                   (uthInput.Keyboard.IsKeyDown(uth::Keyboard::Down) - uthInput.Keyboard.IsKeyDown(uth::Keyboard::Up)) * 100.f * dt);
        textObject->transform.Rotate((uthInput.Mouse.IsButtonDown(uth::Mouse::RIGHT) - uthInput.Mouse.IsButtonDown(uth::Mouse::LEFT)) * 100.f * dt);
    }

    if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::S))
        uthSceneM.SaveCurrentScene("test");
    else if (uthInput.Keyboard.IsKeyPressed(uth::Keyboard::L))
    {
        RemoveChildren();

        uthSceneM.LoadCurrentScene("test");

        textObject = static_cast<GameObject*>(FindAll("TEXT", 1)[0].get());

        auto ps = static_cast<ParticleSystem*>(FindAll("PS", 1)[0].get());
        ps->Clear(true, false);
        setAffectors(ps);
    }
}

//void TestScene::Draw(RenderTarget& target, RenderAttributes attributes)
//{
//	Scene::Draw(target, attributes);
//}
