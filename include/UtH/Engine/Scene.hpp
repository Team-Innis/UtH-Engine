#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

namespace uth
{
	class Scene
	{
	private:
		friend class SceneManager;
		Scene();
		~Scene();

	public:
		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(double dt);
		virtual bool Draw();
	};
}

#endif
