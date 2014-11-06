#pragma once
#ifndef TEXT_H_UTH
#define TEXT_H_UTH

#include <UtH/Engine/Component.hpp>
#include <UtH/Renderer/VertexBuffer.hpp>
#include <UtH/Resources/ResourceManager.hpp>
#include <pmath/Vector.hpp>

// Forward declaration so we dont need to include the ugly C headers
struct texture_atlas_t;
struct texture_font_t;

namespace uth
{
	class Text : public Component
	{
		static std::unordered_set<Text*> TEXTS;

		friend class ResourceManager;
	public:
		Text(const std::string& fontPath, const float fontSize,
			const std::string& name = "Text", 
			const pmath::Vec4 defaultColor = pmath::Vec4(1,1,1,1));
		~Text();

		void Init();

		// Sets the text
		void SetText(const std::string& text);
		void SetText(const std::wstring& text);
		void SetText(const std::string& text, const pmath::Vec4 color);
		void SetText(const std::wstring& text, const pmath::Vec4 color);
		// Adds to the current text
		void AddText(const std::string& text);
		void AddText(const std::wstring& text);
		void AddText(const std::string& text, const pmath::Vec4 color);
		void AddText(const std::wstring& text, const pmath::Vec4 color);
		// Return current text
		const std::wstring& GetText() const;

		void SetColor(const pmath::Vec4 color);
		const pmath::Vec4 GetDefaultColor();

		void Draw(RenderTarget& target);

	private:
		bool RecreateOpenGLContext();
		bool ClearOpenGLContext();


		//Text();
		Text(/*"text", path = "font", size = 32, name = "Text"*/);

        rapidjson::Value save(rapidjson::MemoryPoolAllocator<>& alloc) const final override;

        bool load(const rapidjson::Value& doc) override;


		VertexBuffer m_vertexBuffer;

		const float m_fontSize;
		pmath::Vec2 m_size;
		pmath::Mat4 m_matrix;
		pmath::Vec4 m_color;

		std::wstring m_text;
		// last text cursor pos
		pmath::Vec2 m_lastPos;

		texture_atlas_t* m_atlas;
		texture_font_t* m_font;
	};
}

#endif
