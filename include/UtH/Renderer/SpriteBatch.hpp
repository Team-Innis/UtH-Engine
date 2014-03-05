#pragma once
#ifndef SPRITEBATCH_H_UTH
#define SPRITEBATCH_H_UTH

#include <UtH\Engine\Sprite.hpp>
#include <UtH\Engine\GameObject.hpp>
#include <UtH\Renderer\TextureAtlas.hpp>


namespace uth
{
    class SpriteBatch : public GameObject
    {
    public:

        SpriteBatch();

        ~SpriteBatch();










    private:

        TextureAtlas m_atlas;


    };
}

#endif