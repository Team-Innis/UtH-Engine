#pragma once
#ifndef DefaultScene_H_UTH
#define DefaultScene_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

namespace uth
{
	class DefaultScene : public Scene
	{
	public:
		friend class SceneManager;
		DefaultScene();
		~DefaultScene();

		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(float dt);
		virtual bool Draw();
	protected:

		float totalTime;

		GameObject logo;

		GameObject textU;
		GameObject textT;
		GameObject textH;
		GameObject text;

		GameObject fade;
		Sprite* fadeSprite;

		Text* newestText;
	};
}

#endif
