#include <UtH\Platform\Graphics.hpp>
#include <UtH\Platform\Configuration.hpp>
#include <UtH\Platform\OpenGL.hpp>
#include <UtH\Platform\OGLCheck.hpp>



namespace uth
{
    // Window functions
    bool Graphics::createWindow(const WindowSettings& settings)
    {
        if (m_windowHandle) destroyWindow();

        m_windowSettings = settings;

        // Context settings
        oglCheck(glutInitContextVersion(settings.contextVersionMajor, settings.contextVersionMinor));
        oglCheck(glutInitContextFlags(GLUT_FORWARD_COMPATIBLE));
        oglCheck(glutInitContextProfile(GLUT_CORE_PROFILE));

        // Extra settings
        oglCheck(glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS));

        // Position & size
        oglCheck(glutInitWindowPosition(settings.position.x, settings.position.y));
        oglCheck(glutInitWindowSize(settings.size.x, settings.size.y));

        // Display settings
        oglCheck(glutInitDisplayMode(settings.useBlending ? GLUT_RGBA : GLUT_RGB |
                            settings.useDepthBuffer ? GLUT_DEPTH : 0 |
                            settings.useStencilBuffer ? GLUT_STENCIL : 0 |
                            settings.useDoubleBuffering ? GLUT_DOUBLE : GLUT_SINGLE));
        
        
        m_windowHandle = glutCreateWindow("Generic Window Title");

        int majorVer = settings.contextVersionMajor,
            minorVer = settings.contextVersionMinor;
        
        while (!m_windowHandle)
        {
            if (majorVer < 2) return false;

            minorVer--;

            if (minorVer < 0)
            {
                majorVer--;
                minorVer = 4;
            }

            m_windowHandle = glutCreateWindow("Generic Window Title");
        }

        return true;
    }


    void Graphics::destroyWindow()
    {
        oglCheck(glutDestroyWindow(m_windowHandle));
    }


    void Graphics::clear(const float r, const float g, const float b, const float a = 1.f)
    {
        oglCheck(glClear(GL_COLOR_BUFFER_BIT |
                         m_windowSettings.useDepthBuffer ? GL_DEPTH_BUFFER_BIT : 0 |
                         m_windowSettings.useStencilBuffer ? GL_STENCIL_BUFFER_BIT : 0));
		oglCheck(glClearColor(r, g, b, a));

        if (m_windowSettings.useDepthBuffer) return;

		#ifdef UTH_SYSTEM_OPENGLES
			oglCheck(glClearDepthf(1)); 
		#else
			oglCheck(glClearDepth(1)); 
		#endif 

    }

    void Graphics::swapBuffers()
    {
        oglCheck(glutSwapBuffers());
    }






    // Private

    Graphics::Graphics()
        : m_windowHandle(0),
          m_windowSettings()
    {}

    Graphics::~Graphics()
    {
        destroyWindow();
    }
}