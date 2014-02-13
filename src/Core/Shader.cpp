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
bool Shader::LoadShader(ShaderType type, const std::string path)
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

bool Shader::setAttributeData(const std::string name, const int size, DataType type, const int offset, const void* data)
{
	int location = uthGraphics.getAttributeLocation(program, name.c_str());
	if(location == -1)
		return false;

	uthGraphics.enableVertexAttribArray(location);
	uthGraphics.setVertexAttribPointer(location, size, type, offset, data);
	uthGraphics.disableVertexAttribArray(location);
	return true;
}


//////////////////////////////////////////////////////////////
// Uniform set functions
bool Shader::SetUniform(const std::string name, const float x)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x);
	return true;
}
bool Shader::SetUniform(const std::string name, const float x, const float y)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x, y);
	return true;
}
bool Shader::SetUniform(const std::string name, const float x, const float y, const float z)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x, y, z);
	return true;
}
bool Shader::SetUniform(const std::string name, const float x, const float y, const float z, const float w)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x, y, z, w);
	return true;
}
bool Shader::SetUniform(const std::string name, const umath::vector2& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string name, const umath::vector3& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string name, const umath::vector4& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string name, const umath::matrix3& matrix)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, matrix);
	return true;
}
bool Shader::SetUniform(const std::string name, const umath::matrix4& matrix)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, matrix);
	return true;
}

// Private

