#ifndef SHADER_H_UTH
#define SHADER_H_UTH

#include <unordered_set>
#include <string>
#include <pmath/PMath.hpp>
#include <UtH/Platform/Enums.hpp>
#include <UtH/Resources/Resource.hpp>

namespace uth
{
	class RenderTarget;

	class Shader : Resource
	{
		struct Deleter
		{
			void operator()(Shader* file) const
			{
				delete file;
			}
		};

		friend class ResourceManager;

		Shader();
		~Shader();

	public:

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

		bool LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

		virtual bool LoadFromFile(const std::string& filePath) override;
		virtual void Unload() override;
		//virtual bool EnsureLoaded() override;

		unsigned int m_program;
	};
}

#endif