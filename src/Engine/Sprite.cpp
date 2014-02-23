#include <UtH/Engine/Sprite.hpp>
#include <UtH/Math/Vector3.hpp>

using namespace uth;

Sprite::Sprite(Texture* texture, const std::string name)
	: Component(name)
{
	SetDrawable(true);
	generetateBuffer();

	SetTexture(texture);
}

// Public

Sprite::Sprite(const std::string filePath, const std::string name)
	: Component(name)
{
	SetDrawable(true);
	generetateBuffer();

	Texture* tex = new Texture();
	tex->loadFromFile(filePath.c_str());
	SetTexture(tex);
}

Sprite::~Sprite()
{
	delete vertexBuffer;
}

void Sprite::Draw(Shader *shader)
{
	texture->bind();
	shader->SetUniform("unifSampler", 0);
	vertexBuffer->draw(shader);
}

void Sprite::Update(float dt)
{ }

const umath::vector2 Sprite::GetSize() const
{
	return m_size;
}

void Sprite::SetTexture(Texture* texture)
{
	this->texture = texture;
	m_size = texture->getSize();
}

// Private

void Sprite::generetateBuffer()
{
	vertexBuffer = new VertexBuffer();

	vertexBuffer->addVertex(umath::vector3(-1.0, -1.0, 0), umath::vector2(0.0f, 0.0f)); // vasen alakulma
	vertexBuffer->addVertex(umath::vector3(1.0, -1.0, 0), umath::vector2(1.0f, 0.0f)); // oikea alakulma
	vertexBuffer->addVertex(umath::vector3(-1.0, 1.0, 0), umath::vector2(0.0f, 1.0f)); // vasen yläkulma
	vertexBuffer->addVertex(umath::vector3(1.0, 1.0, 0), umath::vector2(1.0f, 1.0f)); // oikea yläkulma
	vertexBuffer->addIndex(0);
	vertexBuffer->addIndex(1);
	vertexBuffer->addIndex(2);
	vertexBuffer->addIndex(1);
	vertexBuffer->addIndex(3);
	vertexBuffer->addIndex(2);
}
