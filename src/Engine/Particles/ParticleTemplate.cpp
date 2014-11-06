#include <UtH/Engine/Particles/ParticleTemplate.hpp>
#include <UtH/Engine/Randomizer.hpp>
#include <UtH/Engine/Particles/Particle.hpp>

using namespace uth;

ParticleTemplate::ParticleTemplate()
    : lifetime(0.f),
      minSpeed(1.f),
      maxSpeed(0.f),
      color(1),
      m_texture(nullptr)
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

void ParticleTemplate::SetColor(const float r, const float g, const float b, const float a)
{
    color = pmath::Vec4(r, g, b, a);
}