#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

namespace uth
{
	class Scene
	{
		friend class SceneManager;
		Scene();
		~Scene();

	public:
		virtual bool Init();
		virtual bool Update(double dt);
		virtual bool Draw();
		virtual bool DeInit();

	private:
		bool m_initialized;
	};
}

#endif
