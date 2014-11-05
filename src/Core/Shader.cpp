#include <UtH/Core/Shader.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileManager.hpp>
#include <UtH/Platform/Configuration.hpp>
#include <UtH/Platform/Debug.hpp>
#include <UtH/Renderer/RenderTarget.hpp>

using namespace uth;

std::unordered_set<Shader*> Shader::SHADERS;

Shader::Shader()
    : m_program(0),
      m_target(nullptr)
{
	//WriteLog("\nShaderProgram created: %d", program);
}
Shader::~Shader()
{

	ClearOpenGLContext();

    if (m_target)
        m_target->SetShader(nullptr);
}

// Public
bool Shader::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	m_vertexPath = vertexShaderPath;
	m_fragmentPath = fragmentShaderPath;

    if (!m_program)
    {
        //uth::Graphics::DestroyShaderProgram(m_program);
        m_program = uth::Graphics::CreateShaderProgram();

    }

	FileManager fr;

	// Vertex Shader
	fr.OpenFile(vertexShaderPath);

#if defined(UTH_SYSTEM_OPENGLES)
	const std::string vertex = "#version 100\n#define UTH_ES\n" + fr.ReadText(); 
#elif defined(UTH_SYSTEM_OPENGL)
	const std::string vertex = "#version 100\n" + fr.ReadText();
#endif

	if(!uth::Graphics::CreateShader(VERTEX_SHADER, m_program, vertex.c_str()))
	{
		WriteError("Vertex shader failed");
		return false;
	}
    fr.CloseFile();

	// Fragment Shader
	fr.OpenFile(fragmentShaderPath);
	

#if defined(UTH_SYSTEM_OPENGLES)
	const std::string fragment = "#version 100\n#define UTH_ES\nprecision mediump float;\n" + fr.ReadText(); 
#elif defined(UTH_SYSTEM_OPENGL)
	const std::string fragment = "#version 100\nprecision mediump float;\n" + fr.ReadText();
#endif

	if(!uth::Graphics::CreateShader(FRAGMENT_SHADER, m_program, fragment.c_str()))
	{
		WriteError("Fragment shader failed");
		return false;
	}
    fr.CloseFile();
	const bool result = uth::Graphics::LinkShaderProgram(m_program);

	if (result)
		SHADERS.emplace(this);

	return result;
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
bool Shader::SetUniform(const std::string& name, const pmath::Vec2& vector)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const pmath::Vec3& vector)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const pmath::Vec4& vector)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, vector);
	return true;
}
bool Shader::SetUniform(const std::string& name, const pmath::Mat3& matrix)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, matrix);
	return true;
}
bool Shader::SetUniform(const std::string& name, const pmath::Mat4& matrix)
{
	int location = uth::Graphics::GetUniformLocation(m_program, name.c_str());
	if(location == -1)
		return false;
	uth::Graphics::SetUniform(location, matrix);
	return true;
}

// Private

bool Shader::ClearOpenGLContext()
{
	SHADERS.erase(this);

	return true;
}
bool Shader::RecreateOpenGLContext()
{
	if (m_vertexPath == "" || m_fragmentPath == "")
		return false;

	return LoadShader(m_vertexPath, m_fragmentPath);
}
