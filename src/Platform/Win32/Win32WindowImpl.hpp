#include <UtH\Platform\WindowSettings.hpp>


namespace uth
{
    class Win32WindowImpl
    {
    public:

        Win32WindowImpl();
        ~Win32WindowImpl();

        static void* create(const WindowSettings& settings);

        static void* destroy(void* handle);

        static void clear(const bool clearDepth, const bool clearStencil, const float r, const float g, const float b, const float a = 1.f);

        static void swapBuffers(void* handle);

    };
}