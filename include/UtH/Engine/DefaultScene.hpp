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

	class DefaultScene final : public Scene
	{
	public:
		friend class SceneManager;
		DefaultScene();
		~DefaultScene();

		bool Init();
		bool DeInit();

		void Update(float dt);

	protected:

		float totalTime;

		std::shared_ptr<GameObject> logo, textU, textT, textH, text, fade;

		Sprite* fadeSprite;

		Text* newestText;
	};
}

#endif
