#ifndef SHADER_H
#define SHADER_H

#include <UtH/Platform/Enums.hpp>
#include <UtH/Math/Math.hpp>
#include <string>

namespace uth
{
	class Shader
	{
	public:
		Shader();
		~Shader();

		bool LoadShader(ShaderType type, const std::string path);
		bool LinkShader();
		void Use();



		//////////////////////////////////////////////////////////////
		// Uniform set functions
		bool SetUniform(const std::string name, const float x);
        bool SetUniform(const std::string name, const float x, const float y);
        bool SetUniform(const std::string name, const float x, const float y, const float z);
        bool SetUniform(const std::string name, const float x, const float y, const float z, const float w);
		bool SetUniform(const std::string name, const umath::vector2& vector);
		bool SetUniform(const std::string name, const umath::vector3& vector);
		bool SetUniform(const std::string name, const umath::vector4& vector);
		bool SetUniform(const std::string name, const umath::matrix3& matrix);
		bool SetUniform(const std::string name, const umath::matrix4& matrix);
	private:
		int program;
	};
}

#endif