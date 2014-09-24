#pragma once
#ifndef SCENE_H_UTH
#define SCENE_H_UTH

#define UTHDefaultScene -1

#include <UtH/Core/Shader.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Engine/Layer.hpp>
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

		virtual void Update(float dt) final;
		virtual void Draw(RenderTarget& target) final;

		virtual void PreUpdate(float dt){};
		virtual void PostUpdate(float dt){};
		virtual void PreDraw(RenderTarget& target){};
		virtual void PostDraw(RenderTarget& target){};

		//virtual void OnPause();
		//virtual void OnResume();

	protected:

		//LAYERS
		//Layer* CreateLayer(const int layerId, const bool adoptObjects = true);
  //      bool DeleteLayer(const int layerID);
  //      Layer* GetLayer(const int layerID);
		//GameObject* AddGameObjectToLayer(const int layerId, GameObject* gameObject);
		//GameObject* RemoveGameObjectFromLayer(const int LayerId, GameObject* gameObject, const bool deleteObject = true);

  //      // If id < 0, all layers will be updated/drawn.
  //      void UpdateLayers(float dt, const int id = -1);
  //      void DrawLayers(RenderTarget& target, const int id = -1);

    private:

        //struct LayerDeleter
        //{
        //    void operator ()(Layer* layer)
        //    {
        //        delete layer;
        //    }
        //};

        //std::map<int, std::unique_ptr<Layer, LayerDeleter>> m_layers;
	};
}

#endif
