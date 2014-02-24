#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

namespace uth
{
	class Scene
	{
	public:
		friend class SceneManager;
		Scene();
		~Scene();

	public:
		virtual bool Init();
		virtual bool DeInit();

		virtual bool Update(double dt);
		virtual bool Draw();

		/*uth::WindowSettings* settings;
		uth::Shader* shader;
		uth::VertexBuffer* buf;
		uth::Texture* tex;*/

		int number;
	};
}

#endif
