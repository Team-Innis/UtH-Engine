#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

#define UTHDefaultScene -1

#include <UtH/Resources/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <map>

namespace uth
{
	class RenderTarget;

	class Scene : public Layer
    {
        friend class SceneManager;

	public:

		Scene();
		virtual ~Scene() = 0;

		virtual bool Init() = 0;
		virtual bool DeInit() = 0;

		virtual void Update(float dt);
		virtual void Draw(RenderTarget& target, RenderAttributes attributes = RenderAttributes());

	};
}

#endif
