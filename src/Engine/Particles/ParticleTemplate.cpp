#include <UtH/Engine/Particles/ParticleTemplate.hpp>
#include <UtH/Core/Randomizer.hpp>
#include <UtH/Engine/Particles/Particle.hpp>

using namespace uth;

ParticleTemplate::ParticleTemplate()
    : lifetime(0),
      m_texture(nullptr),
      minSpeed(1.f),
      maxSpeed(0.f),
      m_pInitFunc([](Particle& particle, ParticleTemplate& pTemplate)
                  {
                      // Default init function. Will distribute particles to random directions at speeds defined by the template.

                      umath::vector2 tvec(Randomizer::InsideCircle());
                      tvec /= tvec.getLenght();
                      particle.direction = (pTemplate.maxSpeed == 0.f ? pTemplate.minSpeed : (Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed))) * tvec;
                  })
{

}


void ParticleTemplate::SetTexture(Texture* texture, const umath::rectangle& texCoords)
{
    m_texture = texture;
    m_texCoords = texCoords;
}

void ParticleTemplate::SetLifetime(const double seconds)
{
    lifetime = seconds;
}

void ParticleTemplate::SetSpeed(const float pixelsPerSecond)
{
    minSpeed = pixelsPerSecond;
    maxSpeed = 0.f;
}

void ParticleTemplate::SetSpeed(const float pixelsPerSecondMin, const float pixelsPerSecondMax)
{
    minSpeed = pixelsPerSecondMin;
    maxSpeed = pixelsPerSecondMax;
}

void ParticleTemplate::SetInitFunction(std::function<void(Particle&, ParticleTemplate&)> func)
{
    m_pInitFunc = func;
}