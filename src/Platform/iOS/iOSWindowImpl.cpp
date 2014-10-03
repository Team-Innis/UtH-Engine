#include <UtH/Platform/iOS/iOSWindowImpl.hpp>
#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/OGLCheck.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <cassert>


namespace
{
    uth::iOSWindowImpl::ResizeFunc ns_resizeFunc;
}


namespace uth
{
    
    void* iOSWindowImpl::create(const WindowSettings& settings)
    {
        return nullptr;
    }
    
    
    void* iOSWindowImpl::destroy(void* handle)
    {
        return nullptr;
    }
    
    
    void iOSWindowImpl::clear(
                                 const float r,
                                 const float g,
                                 const float b,
                                 const float a,
                                 const bool,
                                 const bool
                                 )
    {
        uth::Graphics::Clear(r, g, b, a);
    }
    
    void iOSWindowImpl::swapBuffers(void* handle)
    {
    }
    
    bool iOSWindowImpl::processMessages(void* handle)
    {
        return true;
    }
    
    void iOSWindowImpl::setResizeCallback(ResizeFunc func)
    {
    }
}