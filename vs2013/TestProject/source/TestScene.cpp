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
	WriteLog("TESTSCENE INIT");
	// Layers
    CreateLayer(Default);
    CreateLayer(Other);

    // Objects
    // First
	{
	    auto test = new GameObject();
		test->AddComponent(new Sprite(pmath::Vec4(1,0,0,1),pmath::Vec2(128,128)));
	    AddGameObjectToLayer(Default, test);
    }

    // Second (ParticleSystem)
    {
        ParticleTemplate pt;
        pt.SetLifetime(1.f);
        pt.SetSpeed(10.f, 150.f);
        pt.SetTexture(uthRS.LoadTexture("particle.tga"));

        auto ps = new ParticleSystem(100);
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
        AddGameObjectToLayer(Other, ps);
    }

	
	//music = Sound::Load("media/music.wav");
	//music->Play();
	//music->Loop(true);

	textObject.AddComponent(text = new Text("8bitoperator.ttf", 64));
	textObject.transform.SetOrigin(pmath::Vec2(0.5f, 0.0f));
	//textObject.transform.SetScale(0);
	text->SetText("testi");

	return true;
}
bool TestScene::DeInit()
{
	WriteLog("TESTSCENE DEINIT");
	return true;
}

bool TestScene::Update(float dt)
{
	if (uthInput.Common == uth::InputEvent::CLICK)
	{
		//uthSceneM.GoToScene(-1);
		text->SetText("CLICK");
	}
	if (uthInput.Touch.Motion() == TouchMotion::RELEASE)
	{
		WriteLog("RELEASE");
	}


#pragma region Controller



	if (uthInput.Controller.IsButtonDown(Controller::ButtonA))
		text->SetText("A");
	else if (uthInput.Controller.IsButtonDown(Controller::ButtonB))
		text->SetText("B");
	else if (uthInput.Controller.IsButtonDown(Controller::ButtonX))
		text->SetText("X");
	else if (uthInput.Controller.IsButtonDown(Controller::ButtonY))
		text->SetText("Y");


	else if (uthInput.Controller.IsButtonDown(Controller::DpadDown))
		text->SetText("DPAD DOWN");
	else if (uthInput.Controller.IsButtonDown(Controller::DpadLeft))
		text->SetText("DPAD LEFT");
	else if (uthInput.Controller.IsButtonDown(Controller::DpadRight))
		text->SetText("DPAD RIGHT");
	else if (uthInput.Controller.IsButtonDown(Controller::DpadUp))
		text->SetText("DPAD UP");
	
	else if (uthInput.Controller.IsButtonDown(Controller::L1))
		text->SetText("L1");
	else if (uthInput.Controller.IsButtonDown(Controller::R1))
		text->SetText("R1");

	else if (uthInput.Controller.IsButtonDown(Controller::Select))
		text->SetText("SELECT");
	else if (uthInput.Controller.IsButtonDown(Controller::Start))
		text->SetText("START");

	else if (uthInput.Controller.IsButtonDown(Controller::ThumbLeft))
		text->SetText("THUMB LEFT");
	else if (uthInput.Controller.IsButtonDown(Controller::ThumbRight))
		text->SetText("THUMB RIGHT");

	else if (uthInput.Controller.GetAxis(Controller::LeftTrigger) >= 0.2f)
		text->SetText("Left Trigger");
	else if (uthInput.Controller.GetAxis(Controller::RightTrigger) >= 0.2f)
		text->SetText("Right Trigger");

	//else if (uthInput.Controller.GetAxis(Controller::DpadX) >= 0.2f)
	//	text->SetText("DPAD X?");
	//else if (uthInput.Controller.GetAxis(Controller::DpadY) >= 0.2f)
	//	text->SetText("DPAD Y?");

	else if (uthInput.Controller.GetAxis(Controller::RightThumbX) >= 0.2f)
		text->SetText("RIGHT THUMB X");
	else if (uthInput.Controller.GetAxis(Controller::RightThumbY) >= 0.2f)
		text->SetText("RIGHT THUMB Y");
	else if (uthInput.Controller.GetAxis(Controller::LeftThumbX) >= 0.2f)
		text->SetText("LEFT THUMB X");
	else if (uthInput.Controller.GetAxis(Controller::LeftThumbY) >= 0.2f)
		text->SetText("LEFT THUMB Y");
#pragma endregion

	
	return true;
}
bool TestScene::Draw()
{
	DrawLayers(uthEngine.GetWindow(), -1);
	textObject.Draw(uthEngine.GetWindow());

	return true;
}

bool TestScene::PauseSounds()
{
	//music->Pause();
	return true;
}