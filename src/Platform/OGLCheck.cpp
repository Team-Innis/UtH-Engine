// Headers
#include <UtH\Platform\OpenGL.hpp>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace uth
{

    void checkGlError(const char* file, const unsigned int line)
    {
        GLenum errCode = glGetError();

        if (errCode != GL_NO_ERROR)
        {
            std::string fileS(file);
            std::string errorS = "unknown error";

            switch(errCode)
            {
                case GL_INVALID_ENUM:
                    errorS = "GL_INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    errorS = "GL_INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    errorS = "GL_INVALID_OPERATION";
                    break;
                case GL_STACK_OVERFLOW:
                    errorS = "GL_STACK_OVERFLOW";
                    break;
                case GL_STACK_UNDERFLOW:
                    errorS = "GL_STACK_UNDERFLOW";
                    break;
                case GL_OUT_OF_MEMORY:
                    errorS = "GL_OUT_OF_MEMORY";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    errorS = "GL_INVALID_FRAMEBUFFER_OPERATION";
                    break;
            }

            errorS += static_cast<char>(line);
            // cout...
        }
    }

} // namespace uth