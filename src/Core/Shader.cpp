#include <UtH/Core/Shader.hpp>
#include <UtH/Platform/Graphics.hpp>
#include <UtH/Platform/FileReader.h>

using namespace uth;

Shader::Shader()
{}

Shader::~Shader()
{}


// Public
Shader::LoadShader(ShaderType type, std::string path)
{
	FileReader fr(path.c_str());

	Graphics.createShader(type, path);
}

// Private

