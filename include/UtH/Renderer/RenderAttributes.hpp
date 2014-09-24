#pragma once
#ifndef RENDERATTRIBUTES_H_UTH
#define RENDERATTRIBUTES_H_UTH


namespace uth
{
    class Shader;
    class Camera;

    struct RenderAttributes
    {
        RenderAttributes(Shader* shdr = nullptr,
                         Camera* cmr = nullptr)
            : shader(shdr),
              camera(cmr)
        {}

        Shader* shader;
        Camera* camera;
    };
}

#endif