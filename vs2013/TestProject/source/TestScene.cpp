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

        Affector* aff = new Affector([](Particle& part, const ParticleTemplate& ptemp, float dt)
        {
            part.Move(part.direction * dt);
        },
        [](float){});

        ps->AddAffector(aff);
        ps->SetEmitProperties(true, 0.05f, 0.1f, 1, 5);
        AddGameObjectToLayer(Other, ps);
    }

	
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
	if (uthInput.Touch.Motion() == TouchMotion::TAP)
	{
		WriteLog("TAP");
	}
	if (uthInput.Controller.IsButtonReleased(Controller::ButtonA))
		music->Pause();
	if (uthInput.Controller.IsButtonDown(Controller::ButtonB))
		WriteLog("B");
	if (uthInput.Controller.IsButtonDown(Controller::ButtonX))
		WriteLog("X");
	if (uthInput.Controller.IsButtonDown(Controller::ButtonY))
		WriteLog("Y");


	if (uthInput.Controller.IsButtonDown(Controller::DpadDown))
		WriteLog("DPAD DOWN");
	if (uthInput.Controller.IsButtonDown(Controller::DpadLeft))
		WriteLog("DPAD LEFT");
	if (uthInput.Controller.IsButtonDown(Controller::DpadRight))
		WriteLog("DPAD RIGHT");
	if (uthInput.Controller.IsButtonDown(Controller::DpadUp))
		WriteLog("DPAD UP");
	
	if (uthInput.Controller.IsButtonDown(Controller::L1))
		WriteLog("L1");
	if (uthInput.Controller.IsButtonDown(Controller::R1))
		WriteLog("R1");

	if (uthInput.Controller.IsButtonPressed(Controller::Select))
		WriteLog("SELECT");
	if (uthInput.Controller.IsButtonDown(Controller::Start))
		WriteLog("START");

	if (uthInput.Controller.IsButtonDown(Controller::ThumbLeft))
		WriteLog("THUMB LEFT");
	if (uthInput.Controller.IsButtonDown(Controller::ThumbRight))
		WriteLog("THUMB RIGHT");

	if (uthInput.Controller.GetAxis(Controller::LeftTrigger, 0.7f))
		WriteLog("Left Trigger");
	if (uthInput.Controller.GetAxis(Controller::RightTrigger, 0.7f))
		WriteLog("Right Trigger");

	if (uthInput.Controller.GetAxis(Controller::DpadX, 0.7f))
		WriteLog("DPAD X?");
	if (uthInput.Controller.GetAxis(Controller::DpadY, 0.7f))
		WriteLog("DPAD Y?");

	if (uthInput.Controller.GetAxis(Controller::RightThumbX, 0.7f))
		WriteLog("RIGHT THUMB X");
	if (uthInput.Controller.GetAxis(Controller::RightThumbY, 0.7f))
		WriteLog("RIGHT THUMB Y");
	if (uthInput.Controller.GetAxis(Controller::LeftThumbX, 0.7f))
		WriteLog("LEFT THUMB X");
	if (uthInput.Controller.GetAxis(Controller::LeftThumbY, 0.7f))
		WriteLog("LEFT THUMB Y");


	return true;
}
bool TestScene::Draw()
{
	DrawLayers(uthEngine.GetWindow(), -1);

	return true;
}
