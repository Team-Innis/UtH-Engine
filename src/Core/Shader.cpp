#include <UtH/Core/Shader.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileReader.h>

using namespace uth;

Shader::Shader()
{
	program = uthGraphics.createShaderProgram();
}

Shader::~Shader()
{}


// Public
bool Shader::LoadShader(ShaderType type, std::string path)
{
	FileReader fr(path.c_str());

	const char* code = fr.ReadText();

	return uthGraphics.createShader(type, program, code);
}

bool Shader::LinkShader()
{
	return uthGraphics.linkShaderProgram(program);
}

void Shader::Use()
{
	uthGraphics.bindProgram(program);
}


//////////////////////////////////////////////////////////////
// Uniform set functions
void Shader::SetUniform(const std::string name, const float x)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, x);
}
void Shader::SetUniform(const std::string name, const float x, const float y)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, x, y);
}
void Shader::SetUniform(const std::string name, const float x, const float y, const float z)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, x, y, z);
}
void Shader::SetUniform(const std::string name, const float x, const float y, const float z, const float w)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, x, y, z, w);
}
void Shader::SetUniform(const std::string name, const umath::vector2& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, vector);
}
void Shader::SetUniform(const std::string name, const umath::vector3& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, vector);
}
void Shader::SetUniform(const std::string name, const umath::vector4& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, vector);
}
void Shader::SetUniform(const std::string name, const umath::matrix3& matrix)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, matrix);
}
void Shader::SetUniform(const std::string name, const umath::matrix4& matrix)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	uthGraphics.setUniform(location, matrix);
}

// Private

