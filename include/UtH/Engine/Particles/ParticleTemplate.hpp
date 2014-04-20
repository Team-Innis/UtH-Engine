#pragma once
#ifndef PARTICLETEMPLATE_H_UTH
#define PARTICLETEMPLATE_H_UTH

#include <UtH/Renderer/Texture.hpp>
#include <UtH/Math/Rectangle.hpp>
#include <string>



namespace uth
{

    class ParticleTemplate
    {
    
        friend class ParticleSystem;

    public:

        ParticleTemplate();


        void SetTexture(Texture* texture, const umath::rectangle& texCoords = umath::rectangle(0.f, 0.f, 1.f, 1.f));

        void SetLifetime(const double seconds);

        void SetSpeed(const float pixelsPerSecond);

        void SetSpeed(const float pixelsPerSecondMin, const float pixelsPerSecondMax);



    private:

        Texture* m_texture;
        umath::rectangle m_texCoords;

        double m_lifetime;
        float m_minSpeed,
              m_maxSpeed;

    };

}

#endif