#include <UtH/Engine/Sprite.hpp>

using namespace uth;

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

Sprite::Sprite(Texture* texture)
{
	SetTexture(texture);
	m_size = texture->getSize();
}

Sprite::Sprite(std::string filePath)
{
	Texture* tex = new Texture();
	tex->loadFromFile(filePath.c_str());
	SetTexture(tex);
	m_size = tex->getSize();
}

void Sprite::Draw()
{
}

void Sprite::Update(float dt)
{
}

const umath::vector2 Sprite::GetSize() const
{
	return m_size;
}

void Sprite::SetTexture(Texture* texture)
{
	this->texture = texture;
}