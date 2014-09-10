#include <UtH/Core/Randomizer.hpp>
#include <pmath/Constants.hpp>
#include <cmath>


using namespace uth;

float Randomizer::GetFloat(const float min, const float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
}

int Randomizer::GetInt(const int min, const int max)
{
    return min + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX/(max-min)));
}

void Randomizer::SetSeed(const unsigned int seed)
{
    std::srand(seed);
}

pmath::Vec2 Randomizer::InsideCircle(const float radius)
{
    const float angle = GetFloat(0.f, static_cast<float>(pmath::tau));
    const float rad = std::sqrt(GetFloat()) * radius;

    return pmath::Vec2(rad * std::cos(angle), rad * std::sin(angle));
}