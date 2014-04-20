#include <UtH/Engine/Particles/ParticleTemplate.hpp>


using namespace uth;

ParticleTemplate::ParticleTemplate()
    : m_lifetime(0),
      m_texture(nullptr),
      m_minSpeed(1.f),
      m_maxSpeed(0.f)
{

}


void ParticleTemplate::SetTexture(Texture* texture, const umath::rectangle& texCoords)
{
    m_texture = texture;
    m_texCoords = texCoords;
}

void ParticleTemplate::SetLifetime(const double seconds)
{
    m_lifetime = seconds;
}

void ParticleTemplate::SetSpeed(const float pixelsPerSecond)
{
    m_minSpeed = pixelsPerSecond;
    m_maxSpeed = 0.f;
}

void ParticleTemplate::SetSpeed(const float pixelsPerSecondMin, const float pixelsPerSecondMax)
{
    m_minSpeed = pixelsPerSecondMin;
    m_maxSpeed = pixelsPerSecondMax;
}