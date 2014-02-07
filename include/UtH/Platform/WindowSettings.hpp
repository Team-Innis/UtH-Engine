#include <UtH\Math\Vector2.hpp>


namespace uth
{
    struct WindowSettings
    {
        WindowSettings()
            : useDepthBuffer(false),
              useStencilBuffer(false),
              useDoubleBuffering(true),
              useBlending(true),

              contextVersionMajor(3),
              contextVersionMinor(3),

              position(100, 100),
              size(800, 600)
        {}


        bool useDepthBuffer,
             useStencilBuffer,
             useDoubleBuffering,
             useBlending;

        int contextVersionMajor,
            contextVersionMinor;

        umath::vector2 position;
        umath::vector2 size;

        // Title...
    };
}