#pragma once
#ifndef SPRITEBATCH_H_UTH
#define SPRITEBATCH_H_UTH

#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/TextureAtlas.hpp>


namespace uth
{
    class SpriteBatch : public GameObject
    {
    public:

        void reserve(const unsigned int amount);

        SpriteBatch();


        void AddSprite(GameObject* object, const std::string& atlasName);

        void SetTextureAtlas(TextureAtlas* atlas);

        void Draw(Shader* shader);


    private:

        std::vector<GameObject*> m_objects;
        TextureAtlas* m_atlas;

        std::vector<Vertex> m_vertexData;
        VertexBuffer m_spriteBuffer;

    };
}

#endif