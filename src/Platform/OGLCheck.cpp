#include <UtH/Platform/OpenGL.hpp>
#include <UtH/Platform/Debug.hpp>
#include <string>
#include <iostream>
#include <sstream>


namespace uth
{

	void checkGlError(const char* file, const unsigned int line, const char* func)
	{
		GLenum errCode = glGetError();

		if (errCode != GL_NO_ERROR)
		{
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
			case GL_OUT_OF_MEMORY:
				errorS = "GL_OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errorS = "GL_INVALID_FRAMEBUFFER_OPERATION";
				break;
			default:
				std::stringstream ss;
				ss << errCode;
				errorS = ss.str();
				break;
			}

			errorS += " on line ";
			std::stringstream ss;
			ss << line;
			errorS += ss.str();
			WriteError("%s \n %s in %s",file, errorS.c_str(), func);

		}
	}

} // namespace uth