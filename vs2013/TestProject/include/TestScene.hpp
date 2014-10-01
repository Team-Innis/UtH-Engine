#pragma once
#ifndef TestScene_H_UTH
#define TestScene_H_UTH

#include <UtH/UtHEngine.hpp>

namespace uth
{
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene() override;
	
        bool Init() override;
        bool DeInit() override;
	
        bool Update(float dt) override;
        bool Draw() override;

		Sound* music;

		GameObject textObject;

		Text* text;
	
	};
}

#endif
