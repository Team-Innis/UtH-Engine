#include <UtH/Engine/DefaultScene.hpp>
#include <UtH/Engine/Engine.hpp>
#include <UtH/Platform/Input.hpp>
#include <UtH/Platform/Android/GooglePlayGameServices.hpp>


using namespace uth;

void bringLetter(std::shared_ptr<GameObject> go, const float startTime, const float endTime, const float totalTime)
{
	if (totalTime > endTime)
		go->transform.SetScale(1/1.5f);
	else if (totalTime > startTime)
		go->transform.SetScale((endTime - startTime) / ((totalTime - startTime) * 1.5f));
}

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
	logo = AddChild<GameObject>();
	text = logo->AddChild<GameObject>();
	textU = logo->AddChild<GameObject>();
	textT = logo->AddChild<GameObject>();
	textH = logo->AddChild<GameObject>();
	fade = AddChild<GameObject>();

	logo->AddComponent(new AnimatedSprite(uthRS.LoadTexture("EngineAnimation.tga"), 60, 6, 10, 20));
	logo->transform.SetPosition(0, 80);
	logo->transform.SetScale(1.5f);

	fadeSprite = new Sprite(pmath::Vec4(0,0,0,0),pmath::Vec2(1280,720));
	fade->AddComponent(fadeSprite);

	textU->AddComponent(newestText = new Text("8bitoperator.ttf", 64,"U"));
	textU->transform.SetOrigin(pmath::Vec2(0.7f * 64.f, 0.8f * 64.f));
	textU->transform.SetPosition(-30, -100);
	textU->transform.SetScale(0);
	newestText->SetText("U", pmath::Vec4(1, 1, 1, 1));

	textT->AddComponent(newestText = new Text("8bitoperator.ttf", 64,"T"));
	textT->transform.SetOrigin(pmath::Vec2(0.0f * 64.f, 0.8f * 64.f));
	textT->transform.SetPosition(0, -100);
	textT->transform.SetScale(0);
	newestText->SetText("T", pmath::Vec4(1, 1, 1, 1));

	textH->AddComponent(newestText = new Text("8bitoperator.ttf", 64,"H"));
	textH->transform.SetOrigin(pmath::Vec2(-0.7f * 64.f, 0.8f * 64.f));
	textH->transform.SetPosition(30, -100);
	textH->transform.SetScale(0);
	newestText->SetText("H", pmath::Vec4(1, 1, 1, 1));

	text->AddComponent(newestText = new Text("8bitoperator.ttf", 32));
	text->transform.SetOrigin(2);
	text->transform.SetPosition(0, -180);
	text->transform.SetScale(1 / 1.5f);
	newestText->SetText("Made with", pmath::Vec4(1,1,1,0));

	totalTime = 0;

    return true;
}
bool DefaultScene::DeInit()
{
	return true;
}

void DefaultScene::Update(float dt)
{
	dt = dt < 0.1f ? dt : 0.1f;
	totalTime += dt;

	Scene::Update(dt);

	const float aStart = 1.0f; // animation start time
	const float aEnd = aStart + 6;

	bringLetter(textU, aStart + 0, aStart + 0.8f, totalTime);
	bringLetter(textT, aStart + 0.5f, aStart + 1.3f, totalTime);
	bringLetter(textH, aStart + 1, aStart + 1.8f, totalTime);

	if (totalTime > aStart + 4)
		newestText->SetText("Made with", pmath::Vec4(1, 1, 1, 1));
	else if (totalTime > aStart + 2)
		newestText->SetText("Made with", pmath::Vec4(1, 1, 1, (totalTime - (aStart + 2)) / 2));

	if (totalTime > aEnd - 1)
		fadeSprite->SetColor(0, 0, 0, 1);
	else if (totalTime > aEnd - 3)
		fadeSprite->SetColor(0, 0, 0, (totalTime - (aEnd - 3)) / 2);
	else if (totalTime < 0.5f)
		fadeSprite->SetColor(0, 0, 0, (0.5f - totalTime) * 2);


	if (uthInput.Common == uth::InputEvent::CLICK)
	{
		
		uthGPGS.leaderboard.SubmitHighScore("CgkI46q954kJEAIQBQ", 9999);

	}
	if (totalTime >= aEnd || uthInput.Common == uth::InputEvent::CLICK)
	{
		uthSceneM.GoToScene(0);
	}
}
