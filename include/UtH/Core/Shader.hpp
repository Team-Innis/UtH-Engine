#ifndef SHADER_H
#define SHADER_H

#include <UtH/Platform/Enums.hpp>
#include <string>

namespace uth
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		void LoadShader(ShaderType type, std::string path);
	};
}

#endif