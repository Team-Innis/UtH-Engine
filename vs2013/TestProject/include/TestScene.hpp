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
	
		//void Update(float dt) override;
		//void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes()) override;

	};
}

#endif
