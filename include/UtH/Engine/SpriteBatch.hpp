#pragma once
#ifndef SPRITEBATCH_H_UTH
#define SPRITEBATCH_H_UTH

#include <UtH/Math/Rectangle.hpp>
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

        SpriteBatch(const bool adoptPointers = true);

        ~SpriteBatch();


        GameObject* AddSprite(GameObject* object, const std::strig& atlasName = "", const umath::vector4& color = umath::vector4(1, 1, 1, 1),
                              const umath::rectangle& texCoords = umath::rectangle(0, 0, 0, 0));

        void SetTextureAtlas(TextureAtlas* atlas);

        void SetTexture(Texture* texture);

        void Clear();


    private:
        
        void draw(RenderTarget& target);


        std::vector<std::unique_ptr<GameObject>> m_objects;
        TextureAtlas* m_atlas;
        Texture* m_texture;

        std::vector<Vertex> m_vertexData;
        VertexBuffer m_spriteBuffer;

        bool m_adoptedPointers;

    };
}

#endif