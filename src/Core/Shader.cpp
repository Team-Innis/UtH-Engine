#include <UtH/Core/Shader.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileReader.h>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

Shader::Shader()
    : m_program(0)
{
	//WriteLog("\nShaderProgram created: %d", program);
}

Shader::~Shader()
{
	uth::Graphics::DestroyShaderProgram(m_program);
}


// Public
bool Shader::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    if (!m_program)
    {
        //uth::Graphics::DestroyShaderProgram(m_program);
        m_program = uth::Graphics::CreateShaderProgram();
    }

	FileReader fr;

	// Vertex Shader
	fr.OpenFile(vertexShaderPath.c_str());
	const char* vertex = fr.ReadText();
	if(!uth::Graphics::CreateShader(VERTEX_SHADER, m_program, vertex))
	{
		WriteError("Vertex shader failed");
		return false;
	}
	delete[] vertex;
    fr.CloseFile();

	// Fragment Shader
	fr.OpenFile(fragmentShaderPath.c_str());
	const char* fragment = fr.ReadText();
	if(!uth::Graphics::CreateShader(FRAGMENT_SHADER, m_program, fragment))
	{
		WriteError("Fragment shader failed");
		return false;
	}
	delete[] fragment;
    fr.CloseFile();

	return uth::Graphics::LinkShaderProgram(m_program);
}

void Shader::Use()
{
	uth::Graphics::BindProgram(m_program);
}

bool Shader::setAttributeData(const std::string& name, const int size, DataType type, const int offset, const void* data)
{
	int location = uth::Graphics::GetAttributeLocation(m_program, name.c_str());
	if(location == -1)
		return false;

	uth::Graphics::EnableVertexAttribArray(location);
	uth::Graphics::SetVertexAttribPointer(location, size, type, offset, data);
	//uthGraphics.disableVertexAttribArray(location);
	return true;
}


//////////////////////////////////////////////////////////////
// Uniform set functions
bool Shader::SetUniform(const std::string& name, const int x)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, x);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, x);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x, const float y)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, x, y);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x, const float y, const float z)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, x, y, z);
	return true;
}
bool Shader::SetUniform(const std::string& name, const float x, const float y, const float z, const float w)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, x, y, z, w);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::vector2& vector)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::vector3& vector)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::vector4& vector)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::matrix3& matrix)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, matrix);
	return true;
}
bool Shader::SetUniform(const std::string& name, const umath::matrix4& matrix)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, matrix);
	return true;
}

// Private

