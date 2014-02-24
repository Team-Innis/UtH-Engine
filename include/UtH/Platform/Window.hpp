#include <UtH\Platform\WindowSettings.hpp>
#include <UtH\Platform\Uncopyable.hpp>



namespace uth
{
    class Window : private Uncopyable
    {
    public:

        Window();

        Window(const WindowSettings& settings);

        ~Window();

        bool create(const WindowSettings& settings);

        void destroy();

        void clear(const float r, const float g, const float b, const float a = 1.f);

        void swapBuffers();

        void setViewport(const int x, const int y, const unsigned int width, const unsigned int height);

        const WindowSettings& getWindowSettings() const;

		void processMessages();




    private:

        void* m_windowHandle;
        WindowSettings m_windowSettings;

    };
}