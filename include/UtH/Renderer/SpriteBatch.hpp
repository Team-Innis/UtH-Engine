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

        SpriteBatch();


        void AddSprite(GameObject* object, const umath::vector2& spriteSize, const std::string& atlasName);

        void SetTextureAtlas(TextureAtlas* atlas);

        void Draw(Shader* shader);


    private:

        void updateMatrixData();

        std::vector<GameObject*> m_objects;
        TextureAtlas* m_atlas;

        std::vector<umath::matrix4> m_matrixData;
        VertexBuffer m_matrixBuffer;
        VertexBuffer m_spriteBuffer;

    };
}

#endif