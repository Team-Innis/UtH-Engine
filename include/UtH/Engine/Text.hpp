#pragma once
#ifndef TEXT_H_UTH
#define TEXT_H_UTH

#include <UtH/Engine/Component.hpp>
#include <UtH/Math/Vector.hpp>
#include <UtH/Core/VertexBuffer.hpp>

struct texture_atlas_t;

namespace uth
{
	class Text : public Component
	{
	public:
		Text(const std::string& fontPath, const std::string& name = "Text");
		~Text();

		void SetText(const std::wstring& text, const float size, 
			/*umath::vector2& position,*/ umath::vector4& color = umath::vector4(1, 1, 1, 1));

		std::wstring& GetText();

		void Update(float dt);
		void Draw(Shader* shader, Camera* camera);

	private:
		Text();

		Shader m_textShader;

		VertexBuffer m_vertexBuffer;

		std::string m_path;

		std::wstring m_text;

		texture_atlas_t* m_atlas;
	};
}

#endif