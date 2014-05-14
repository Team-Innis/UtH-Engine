#include <UtH/Engine/DefaultScene.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/UtHEngine.h>
#include <UtH/Platform/Input.hpp>
#include <UtH/Renderer/TextureAtlas.hpp>
#include <UtH/Platform/Configuration.hpp>

#include <UtH/Platform/Debug.hpp>

using namespace uth;

void bringLetter(GameObject* go, const float startTime, const float endTime, const float totalTime)
{
	if (totalTime > endTime)
		go->transform.SetScale(1);
	else if (totalTime > startTime)
		go->transform.SetScale((endTime - startTime) / (totalTime - startTime));
}

DefaultScene::DefaultScene()
{}
DefaultScene::~DefaultScene()
{}

bool DefaultScene::Init()
{
    shader = new Shader();
    shader->LoadShader("Shaders/Default.vert", "Shaders/Default.frag");
    shader->Use();

    uthEngine.GetWindow().SetViewport(umath::rectangle(0, 0, uthEngine.GetWindowResolution().x, uthEngine.GetWindowResolution().y));
    uthEngine.GetWindow().SetShader(shader);

    logo = new GameObject();
	textU = new GameObject();
	textT = new GameObject();
	textH = new GameObject();
	text = new GameObject();
	fade = new GameObject();

	logo->AddComponent(new AnimatedSprite(&uthRS.LoadTexture("EngineAnimation.tga"),60,6,10,20));
    logo->transform.SetPosition(0, 80);
	logo->transform.SetScale(1.5f);

	fadeSprite = new Sprite(umath::vector4(0,0,0,0),umath::vector2(1280,720));
	fade->AddComponent(fadeSprite);

	textU->AddComponent(newestText = new Text("8bitoperator.ttf",64));
	textU->transform.SetOrigin(umath::vector2(0.7f,0.8f));
	textU->transform.SetPosition(-50,-80);
	textU->transform.SetScale(0);
	newestText->SetText("U");

	textT->AddComponent(newestText = new Text("8bitoperator.ttf",64));
	textT->transform.SetOrigin(umath::vector2(0.0f,0.8f));
	textT->transform.SetPosition(0,-80);
	textT->transform.SetScale(0);
	newestText->SetText("T");

	textH->AddComponent(newestText = new Text("8bitoperator.ttf",64));
	textH->transform.SetOrigin(umath::vector2(-0.7f,0.8f));
	textH->transform.SetPosition(50,-80);
	textH->transform.SetScale(0);
	newestText->SetText("H");

	text->AddComponent(newestText = new Text("8bitoperator.ttf",32));
	text->transform.SetOrigin(2);
	text->transform.SetPosition(0,-200);
	newestText->SetText("Made with", umath::vector4(1,1,1,0));

	totalTime = 0;

    return true;
}
bool DefaultScene::DeInit()
{
    delete logo;
	delete textU;
	delete textT;
	delete textH;
	delete text;

    return true;
}

bool DefaultScene::Update(float dt)
{
	dt = dt < 0.1f ? dt : 0.1f;
	totalTime += dt;

	logo->Update(dt);

	text->Draw(uthEngine.GetWindow());
	textU->Draw(uthEngine.GetWindow());
	textT->Draw(uthEngine.GetWindow());

	const float aStart = 3.0f; // animation start time
	const float aEnd = aStart + 11;

	bringLetter(textU,aStart+0,aStart+1,totalTime);
	bringLetter(textT,aStart+1,aStart+2,totalTime);
	bringLetter(textH,aStart+2,aStart+3,totalTime);

	if (totalTime > aStart+7)
		newestText->SetText("Made with", umath::vector4(1,1,1,1));
	else if (totalTime > aStart+4)
		newestText->SetText("Made with", umath::vector4(1,1,1,(totalTime - (aStart+3)) / 3));

	if (totalTime > aEnd-2)
		fadeSprite->SetColor(0,0,0,1);
	else if (totalTime > aEnd-4)
		fadeSprite->SetColor(0,0,0,(totalTime - (aEnd-4))/2);
	else if (totalTime < 2)
		fadeSprite->SetColor(0,0,0,(2 - totalTime)/2);



	if(totalTime >= aEnd || uthInput.Common == uth::InputEvent::CLICK)
    {
        uthSceneM.GoToScene(0);
	}
    return true;
}
bool DefaultScene::Draw()
{
	uthEngine.GetWindow().Clear(0,0,0,1);
    logo->Draw(uthEngine.GetWindow());
	textU->Draw(uthEngine.GetWindow());
	textT->Draw(uthEngine.GetWindow());
	textH->Draw(uthEngine.GetWindow());
	text->Draw(uthEngine.GetWindow());
	fade->Draw(uthEngine.GetWindow());


    return true;
}