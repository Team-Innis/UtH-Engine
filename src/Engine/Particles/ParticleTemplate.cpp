#include <UtH/Engine/Particles/ParticleTemplate.hpp>
#include <UtH/Core/Randomizer.hpp>
#include <UtH/Engine/Particles/Particle.hpp>

using namespace uth;

ParticleTemplate::ParticleTemplate()
    : lifetime(0.f),
      minSpeed(1.f),
      maxSpeed(0.f),
      color(1),
      m_texture(nullptr),
      m_pInitFunc([](Particle& particle, const ParticleTemplate& pTemplate)
                  {
                      // Default init function. Will distribute particles to random directions at speeds defined by the template.

                      pmath::Vec2 tvec(Randomizer::InsideCircle());
                      tvec /= static_cast<float>(tvec.length());
                      particle.direction = Randomizer::GetFloat(pTemplate.minSpeed, pTemplate.maxSpeed) * tvec;
                  })
{

}


void ParticleTemplate::SetTexture(Texture* texture, const pmath::Rect& texCoords)
{
    m_texture = texture;
    m_texCoords = texCoords;
}

void ParticleTemplate::SetLifetime(const float seconds)
{
    lifetime = seconds;
}

void ParticleTemplate::SetSpeed(const float pixelsPerSecond)
{
    minSpeed = pixelsPerSecond;
    maxSpeed = pixelsPerSecond;
}

void ParticleTemplate::SetSpeed(const float pixelsPerSecondMin, const float pixelsPerSecondMax)
{
    minSpeed = pixelsPerSecondMin;
    maxSpeed = pixelsPerSecondMax;
}

void ParticleTemplate::SetInitFunction(ParticleInitFunc func)
{
    m_pInitFunc = func;
}

void ParticleTemplate::SetColor(const float r, const float g, const float b, const float a)
{
    color = pmath::Vec4(r, g, b, a);
}