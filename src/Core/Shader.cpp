#include <UtH/Core/Shader.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

Shader::Shader()
{
	program = uthGraphics.createShaderProgram();
	//WriteLog("\nShaderProgram created: %d", program);
}

Shader::~Shader()
{}


// Public
bool Shader::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	FileReader fr;

	// Vertex Shader
	fr.OpenFile(vertexShaderPath.c_str());
	const char* vertex = fr.ReadText();
	if(!uthGraphics.createShader(VERTEX_SHADER, program, vertex))
	{
		WriteLog("Vertex shader failed");
		return false;
	}

	// Fragment Shader
	fr.OpenFile(fragmentShaderPath.c_str());
	const char* fragment = fr.ReadText();
	if(!uthGraphics.createShader(FRAGMENT_SHADER, program, fragment))
	{
		WriteLog("Fragment shader failed");
		return false;
	}

	return uthGraphics.linkShaderProgram(program);
}

void Shader::Use()
{
	uthGraphics.bindProgram(program);
}

bool Shader::setAttributeData(const std::string& name, const int size, DataType type, const int offset, const void* data)
{
	int location = uthGraphics.getAttributeLocation(program, name.c_str());
	if(location == -1)
		return false;

	uthGraphics.enableVertexAttribArray(location);
	uthGraphics.setVertexAttribPointer(location, size, type, offset, data);
	//uthGraphics.disableVertexAttribArray(location);
	return true;
}


//////////////////////////////////////////////////////////////
// Uniform set functions
bool Shader::SetUniform(const std::string& name, const int x)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x, const float y)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x, y);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x, const float y, const float z)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x, y, z);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x, const float y, const float z, const float w)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, x, y, z, w);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::vector2& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::vector3& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::vector4& vector)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::matrix3& matrix)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, matrix);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::matrix4& matrix)
{
	int location = uthGraphics.getUniformLocation(program, name.c_str());
	if(location == -1)
		return false;
	uthGraphics.setUniform(location, matrix);
	return true;
}

// Private

