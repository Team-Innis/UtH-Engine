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
}

// Private

