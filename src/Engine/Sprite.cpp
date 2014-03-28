#include <UtH/Engine/Sprite.hpp>
#include <UtH/Math/Vector3.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Renderer/RenderTarget.hpp>
#include <UtH/Platform/Graphics.hpp>

using namespace uth;

Sprite::Sprite(Texture* texture, const std::string& name)
	: Component(name),
      m_texture(texture)
{
	defaults();
}

// Public

Sprite::Sprite(const std::string& filePath, const std::string& name)
	: Component(name)
{
	Texture* tex = new Texture();
	tex->LoadFromFile(filePath.c_str());
	SetTexture(tex);

	defaults();
}

Sprite::Sprite(const umath::vector4& fillColor, const umath::vector2& size, const std::string& name)
	: Component(name),
      m_texture(nullptr)
{
	m_size = size;
	m_isSizeSet = false;
	SetColor(fillColor);
}


Sprite::~Sprite()
{
	m_texture = nullptr;
}

void Sprite::Update(float dt)
{
	generateBuffer();
}

void Sprite::Draw(RenderTarget& target)
{
    Shader& shader = target.GetShader();

	if (!m_isSizeSet)
		return;

	if (m_texture)
	{
		m_texture->Bind();
		shader.SetUniform("useTexture", 1.f);
		shader.SetUniform("unifSampler", 0);
	}
	else
	{
		shader.SetUniform("useTexture", 0.f);
	}

    m_vertexBuffer.bindArrayBuffer();
	// (position + uv + color) * sizeof(float)
	const int posOffset = (3 + 2 + 4)*sizeof(float);
	// position * sizeof(float)
	const int uvStart = 3*sizeof(float);
	// (position + uv) * sizeof(float)
	const int colorStart = (3 + 2)*sizeof(float);

	// Attribute name, number of components, datatype, bytes between first elements,
	// offset of first element in buffer
	shader.setAttributeData("attrPosition", 3, FLOAT_TYPE, posOffset, (void*)0);
	shader.setAttributeData("attrUV", 2, FLOAT_TYPE, posOffset, (void*)uvStart);
	shader.setAttributeData("attrColor", 4, FLOAT_TYPE, posOffset, (void*)colorStart);

    m_vertexBuffer.bindElementBuffer();
    uth::Graphics::DrawElements(TRIANGLES, m_vertexBuffer.getIndices().size(), UNSIGNED_SHORT_TYPE, (void*)0);

	uth::Graphics::BindBuffer(ARRAY_BUFFER, 0);
}

void Sprite::SetTexture(Texture* texture)
{
	m_texture = texture;
	m_size = texture->GetSize();
}

Texture* Sprite::GetTexture() const
{
	return m_texture;
}

const umath::vector2& Sprite::GetSize() const
{
	return m_size;
}

void Sprite::SetColor(const umath::vector4& color)
{
	m_color = color;
	m_vertexBuffer.clear();
	m_bufferNeedsUpdate = true;
}

void Sprite::SetColor(float r, float g, float b, float a)
{
	SetColor(umath::vector4(r,g,b,a));
}


const umath::vector4& Sprite::GetColor() const
{
	return m_color;
}


// Private
void Sprite::defaults()
{
    m_size = m_texture->GetSize();
	m_color = umath::vector4(1.f, 1.f, 1.f, 1.f);

	m_bufferNeedsUpdate = true;
	m_isSizeSet = false;
}



void Sprite::generateBuffer()
{
	if(!m_bufferNeedsUpdate)
		return;

	//m_vertexBuffer.addVertex(Vertex(umath::vector3(-m_size.x/2, -m_size.y/2, 0),
	//	umath::vector2(1.0f, 1.0f), m_color));
	//m_vertexBuffer.addVertex(Vertex(umath::vector3(m_size.x/2, -m_size.y/2, 0),
	//	umath::vector2(0.0f, 1.0f), m_color));
	//m_vertexBuffer.addVertex(Vertex(umath::vector3(-m_size.x/2, m_size.y/2, 0),
	//	umath::vector2(1.0f, 0.0f), m_color));
	//m_vertexBuffer.addVertex(Vertex(umath::vector3(m_size.x/2, m_size.y/2, 0),
	//	umath::vector2(0.0f, 0.0f), m_color));

	m_vertexBuffer.addVertex(Vertex(umath::vector3(-0.5f, -0.5f, 0),
		umath::vector2(0.0f, 1.0f), m_color));
	m_vertexBuffer.addVertex(Vertex(umath::vector3(0.5f, -0.5f, 0),
		umath::vector2(1.0f, 1.0f), m_color));
	m_vertexBuffer.addVertex(Vertex(umath::vector3(-0.5f, 0.5f, 0),
		umath::vector2(0.0f, 0.0f), m_color));
	m_vertexBuffer.addVertex(Vertex(umath::vector3(0.5f, 0.5f, 0),
		umath::vector2(1.0f, 0.0f), m_color));


	m_vertexBuffer.addIndex(0);
	m_vertexBuffer.addIndex(1);
	m_vertexBuffer.addIndex(2);
	m_vertexBuffer.addIndex(1);
	m_vertexBuffer.addIndex(3);
	m_vertexBuffer.addIndex(2);

	if(!m_isSizeSet)
	{
		parent->transform.SetSize(m_size);
		m_isSizeSet = true;
	}
}
