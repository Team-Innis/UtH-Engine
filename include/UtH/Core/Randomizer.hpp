#pragma once
#ifndef RANDOMIZER_H_UTH
#define RANDOMIZER_H_UTH

#include <UtH/Math/Vector2.hpp>
#include <cstdlib>
#include <ctime>


namespace uth
{

    class Randomizer
    {

    public:

        static float GetFloat(const float min = 0.f, const float max = 1.f);

        static int GetInt(const int min, const int max);

        static void SetSeed(const unsigned int seed = std::time(0));

        static umath::vector2 InsideCircle(const float radius = 1.f);


    private:

        Randomizer(){};

    };

}

#endif