#include <UtH\Math\Vector2.hpp>
#include <string>


namespace uth
{
    struct WindowSettings
    {
        WindowSettings()
            : useDepthBuffer(false),
              useStencilBuffer(false),
              useBlending(true),
              useVsync(false),

              contextVersionMajor(3),
              contextVersionMinor(3),

              position(100, 100),
              size(800, 600),

              title("Generic window title")
        {}


        bool useDepthBuffer,
             useStencilBuffer,
             useBlending,
             useVsync;

        int contextVersionMajor,
            contextVersionMinor;

        umath::vector2 position;
        umath::vector2 size;

        std::string title;
    };
}