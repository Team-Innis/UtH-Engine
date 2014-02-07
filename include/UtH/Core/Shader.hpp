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

		bool LoadShader(ShaderType type, std::string path);
		bool LinkShader();
		void Use();



		//////////////////////////////////////////////////////////////
		// Uniform set functions
		void SetUniform(const std::string name, const float x);
        void SetUniform(const std::string name, const float x, const float y);
        void SetUniform(const std::string name, const float x, const float y, const float z);
        void SetUniform(const std::string name, const float x, const float y, const float z, const float w);
		void SetUniform(const std::string name, const umath::vector2& vector);
		void SetUniform(const std::string name, const umath::vector3& vector);
		void SetUniform(const std::string name, const umath::vector4& vector);
		void SetUniform(const std::string name, const umath::matrix3& matrix);
		void SetUniform(const std::string name, const umath::matrix4& matrix);
	private:
		int program;
	};
}

#endif