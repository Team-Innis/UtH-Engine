#pragma once
#ifndef SPRITEBATCH_H_UTH
#define SPRITEBATCH_H_UTH

#include <UtH\Engine\Sprite.hpp>


namespace uth
{
    class SpriteBatch : public GameObject
    {
    public:

        SpriteBatch();

        ~SpriteBatch();













        SpriteBatch& operator <<(const Sprite& sprite); 


    private:

    };
}

#endif