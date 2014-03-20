#include <UtH/Engine/Sprite.hpp>
#include <UtH/Math/Vector3.hpp>

using namespace uth;

Sprite::Sprite(Texture* texture, const std::string name)
	: Component(name)
{
	SetTexture(texture);

	defaults();
}

// Public

Sprite::Sprite(const std::string filePath, const std::string name)
	: Component(name)
{
	Texture* tex = new Texture();
	tex->LoadFromFile(filePath.c_str());
	SetTexture(tex);

	defaults();
}

Sprite::~Sprite()
{
}

void Sprite::Draw(Shader *shader, Camera* camera)
{
    if (m_texture)
	    m_texture->Bind();

	shader->SetUniform("unifSampler", 0);
	m_vertexBuffer.draw(shader);
}

void Sprite::SetTexture(Texture* texture)
{
	m_texture = texture;

    if (m_texture)
	    m_size = texture->GetSize();
}

Texture* Sprite::GetTexture() const
{
	return m_texture;
}

const umath::vector2 Sprite::GetSize() const
{
	return m_size;
}

void Sprite::setSize(const umath::vector2& size)
{
    m_size = size;
}

void Sprite::SetColor(const umath::vector4 color)
{
	m_color = color;
	m_vertexBuffer.clear();
	generetateBuffer();
}

void Sprite::SetColor(float r, float g, float b, float a)
{
	SetColor(umath::vector4(r,g,b,a));
}


const umath::vector4 Sprite::GetColor() const
{
	return m_color;
}


// Private
void Sprite::defaults()
{
    if (m_texture)
        m_size = m_texture->GetSize();

	m_color = umath::vector4(1.f, 1.f, 1.f, 1.f);

	generetateBuffer();
}



void Sprite::generetateBuffer()
{
	m_vertexBuffer.addVertex(Vertex(umath::vector3(-m_size.x/2, -m_size.y/2, 0),
		umath::vector2(1.0f, 1.0f), m_color));
	m_vertexBuffer.addVertex(Vertex(umath::vector3(m_size.x/2, -m_size.y/2, 0),
		umath::vector2(0.0f, 1.0f), m_color));
	m_vertexBuffer.addVertex(Vertex(umath::vector3(-m_size.x/2, m_size.y/2, 0),
		umath::vector2(1.0f, 0.0f), m_color));
	m_vertexBuffer.addVertex(Vertex(umath::vector3(m_size.x/2, m_size.y/2, 0),
		umath::vector2(0.0f, 0.0f), m_color));


	m_vertexBuffer.addIndex(0);
	m_vertexBuffer.addIndex(1);
	m_vertexBuffer.addIndex(2);
	m_vertexBuffer.addIndex(1);
	m_vertexBuffer.addIndex(3);
	m_vertexBuffer.addIndex(2);
}
