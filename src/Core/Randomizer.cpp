#include <UtH/Core/Randomizer.hpp>


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