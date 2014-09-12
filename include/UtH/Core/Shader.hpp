#ifndef SHADER_H_UTH
#define SHADER_H_UTH

#include <pmath/PMath.hpp>
#include <UtH/Platform/Enums.hpp>
#include <string>

namespace uth
{
	class Shader
	{

        friend class RenderTarget;

	public:
		Shader();
		~Shader();

		bool LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		void Use();

		bool setAttributeData(const std::string& name, const int size, DataType type, const int offset, const void* data);



		//////////////////////////////////////////////////////////////
		// Uniform set functions
		bool SetUniform(const std::string& name, const int x);
		bool SetUniform(const std::string& name, const float x);
        bool SetUniform(const std::string& name, const float x, const float y);
        bool SetUniform(const std::string& name, const float x, const float y, const float z);
        bool SetUniform(const std::string& name, const float x, const float y, const float z, const float w);
		bool SetUniform(const std::string& name, const pmath::Vec2& vector);
		bool SetUniform(const std::string& name, const pmath::Vec3& vector);
		bool SetUniform(const std::string& name, const pmath::Vec4& vector);
		bool SetUniform(const std::string& name, const pmath::Mat3& matrix);
		bool SetUniform(const std::string& name, const pmath::Mat4& matrix);
	private:

		unsigned int m_program;

        // Used for unbinding this shader from a render target automatically.
        RenderTarget* m_target;

	};
}

#endif