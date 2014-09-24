#pragma once
#ifndef DefaultScene_H_UTH
#define DefaultScene_H_UTH

#include <UtH/Engine/Scene.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Text.hpp>
#include <UtH/Engine/AnimatedSprite.hpp>

namespace uth
{
	class RenderTarget;

	class DefaultScene : public Scene
	{
	public:
		friend class SceneManager;
		DefaultScene();
		~DefaultScene();

		virtual bool Init();
		virtual bool DeInit();

		virtual void PreUpdate(float dt);
		//virtual void Draw(RenderTarget& target);
	protected:

		float totalTime;

		std::shared_ptr<GameObject> logo, textU, textT, textH, text, fade;

		Sprite* fadeSprite;

		Text* newestText;
	};
}

#endif
