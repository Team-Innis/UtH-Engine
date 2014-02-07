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

		bool LoadShader(ShaderType type, std::string path);
		bool LinkShader();
		void Use();
	private:
		int program;
	};
}

#endif