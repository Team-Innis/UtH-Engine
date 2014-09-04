#pragma once
#ifndef PARTICLETEMPLATE_H_UTH
#define PARTICLETEMPLATE_H_UTH

#include <UtH/Renderer/Texture.hpp>
#include <UtH/Math/Rectangle.hpp>
#include <UtH/Math/Vector4.hpp>
#include <string>
#include <functional>



namespace uth
{
    class Particle;

    class ParticleTemplate
    {
 
        friend class ParticleSystem;
        typedef std::function<void(Particle&, const ParticleTemplate&)> ParticleInitFunc;

    public:

        ParticleTemplate();


        void SetTexture(Texture* texture, const umath::rectangle& texCoords = umath::rectangle(0.f, 0.f, 1.f, 1.f));

        void SetLifetime(const float seconds);

        void SetSpeed(const float pixelsPerSecond);

        void SetSpeed(const float pixelsPerSecondMin, const float pixelsPerSecondMax);

        /// Function for particle initialization. The initial transform will be copied from the ParticleSystem to which this template is bound.
        void SetInitFunction(ParticleInitFunc func);

        void SetColor(const float r, const float g, const float b, const float a);


        float lifetime;
        float minSpeed,
              maxSpeed;
     
        umath::vector4 color;

    private:

        Texture* m_texture;
        umath::rectangle m_texCoords;

        ParticleInitFunc m_pInitFunc;

    };

}

#endif