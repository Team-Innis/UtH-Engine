#pragma once
#ifndef WINDOWIMPL_H_UTH
#define WINDOWIMPL_H_UTH

#include <UtH/Platform/WindowSettings.hpp>
#include <functional>

namespace uth
{
    class iOSWindowImpl
    {
    public:
        
        typedef std::function<void(int, int)> ResizeFunc;
        
    public:
        
        iOSWindowImpl();
        ~iOSWindowImpl();
        
        static void* create(const WindowSettings& settings);
        static void* destroy(void* handle);
        
        static void clear(
                          const float r,
                          const float g,
                          const float b,
                          const float a = 1.f,
                          const bool clearDepth = true,
                          const bool clearStencil = false
                          );
        
        static void swapBuffers(void* handle);
        
        // return true while window should remain open
        static bool processMessages(void* handle);
        
        static void setResizeCallback(ResizeFunc func);
    };
}

#endif