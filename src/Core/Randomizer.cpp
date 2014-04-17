#include <UtH/Core/Randomizer.hpp>
#include <cmath>


using namespace uth;

const float PI = 3.14159265358979323846264f;

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

umath::vector2 Randomizer::InsideCircle(const float radius)
{
    const float angle = GetFloat(0.f, 2 * PI);
    const float rad = std::sqrt(GetFloat()) * radius;

    return umath::vector2(rad * std::cos(angle), rad * std::sin(angle));
}