#pragma once
#ifndef SPRITEBATCH_H_UTH
#define SPRITEBATCH_H_UTH

#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/TextureAtlas.hpp>


namespace uth
{
    class RenderTarget;

    class SpriteBatch : public GameObject
    {
    public:

        void reserve(const unsigned int amount);

        SpriteBatch();


        bool AddSprite(GameObject* object, const std::string& atlasName = "");

        void SetTextureAtlas(TextureAtlas* atlas);

        void SetTexture(Texture* texture);


        void Clear();


    private:

        void draw(RenderTarget& target);

        std::vector<GameObject*> m_objects;
        TextureAtlas* m_atlas;
        Texture* m_texture;

        std::vector<Vertex> m_vertexData;
        VertexBuffer m_spriteBuffer;

    };
}

#endif