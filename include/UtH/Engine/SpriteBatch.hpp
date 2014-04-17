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


        GameObject* AddSprite(GameObject* object, const std::string& atlasName = "");

        void SetTextureAtlas(TextureAtlas* atlas);

        void SetTexture(Texture* texture);

        void Draw(RenderTarget& target);


    private:

        std::vector<std::unique_ptr<GameObject>> m_objects;
        TextureAtlas* m_atlas;
        Texture* m_texture;

        std::vector<Vertex> m_vertexData;
        VertexBuffer m_spriteBuffer;

    };
}

#endif