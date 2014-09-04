#pragma once
#ifndef SPRITEBATCH_H_UTH
#define SPRITEBATCH_H_UTH

#include <pmath/Rectangle.hpp>
#include <UtH/Engine/Sprite.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/TextureAtlas.hpp>


namespace uth
{
    class RenderTarget;

    class SpriteBatch : public GameObject
    {
    public:

        SpriteBatch(const bool adoptPointers = true);

        ~SpriteBatch();


        void AddSprite(Transform* object, const std::string& atlasName = "", const pmath::Vec4& color = pmath::Vec4(1, 1, 1, 1),
                              const pmath::Rect& texCoords = pmath::Rect(0, 0, 0, 0));

        void SetTextureAtlas(TextureAtlas* atlas);

        void SetTexture(Texture* texture);

        void Clear();


    protected:

        virtual void draw(RenderTarget& target);


        std::vector<std::unique_ptr<Transform>> m_objects;
        TextureAtlas* m_atlas;
        Texture* m_texture;

        std::vector<Vertex> m_vertexData;
        VertexBuffer m_spriteBuffer;

        bool m_adoptedPointers;

    };
}

#endif