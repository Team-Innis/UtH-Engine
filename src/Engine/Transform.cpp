#include <UtH/Engine/Transform.hpp>

using namespace uth;

Transform::Transform(const std::string name)
	: Component(name),
	  position(0, 0),
	  size(1, 1),
	  angle(0),
	  depth(0),
	  transformNeedsUpdate(false)
{ }

Transform::~Transform()
{ }

// Public

void Transform::Move(umath::vector2 offset)
{
	position += offset;
	transformNeedsUpdate = true;
}

void Transform::Move(float offsetX, float offsetY)
{
	Move(umath::vector2(offsetX, offsetY));
}

void Transform::SetPosition(umath::vector2 position)
{
	this->position = position;
	transformNeedsUpdate = true;
}

void Transform::SetPosition(float posX, float posY)
{
	SetPosition(umath::vector2(posX, posY));
}

const umath::vector2& Transform::GetPosition() const
{
	return position;
}

void Transform::SetSize(umath::vector2 size)
{
	this->size = size;
	transformNeedsUpdate = true;
}

void Transform::SetSize(float width, float height)
{
	SetSize(umath::vector2(width, height));
}

const umath::vector2& Transform::GetSize() const
{
	return size;
}

void Transform::SetRotation(float angle)
{
	this->angle = angle;
	transformNeedsUpdate = true;
}

const float Transform::GetRotation() const
{
	return angle;
}


void Transform::Rotate(float angle)
{
	this->angle += angle;
	transformNeedsUpdate = true;
}

void Transform::SetDepth(float depth)
{
	this->depth = depth;
	transformNeedsUpdate = true;
}

const float Transform::GetDepth() const
{
	return depth;
}

const umath::matrix4& Transform::GetTransform()
{
	updateTransform();

	return m_modelTransform;
}

// Private

void Transform::updateTransform()
{
	if(transformNeedsUpdate)
	{
		float ang = -angle * PI / 180.f;
		float cosine = std::cos(ang);
		float sine = std::sin(ang);

		umath::matrix4 rotation(cosine, -sine,  0,    0,
								sine,   cosine, 0,    0,
								0,      0,      1.0f, 0,
								0,      0,      0,    1.0f);

		umath::matrix4 scale(size.x, 0,      0,    0,
							 0,      size.y, 0,    0,
							 0,      0,      1.0f, 0,
							 0,      0,      0,    1.0f);

		umath::matrix4 translation(1.0f,       0,          0,     0,
								   0,          1.0f,       0,     0,
								   0,          0,          1.0f,  1.0f,
								   position.x, position.y, depth, 1.0f);

		m_modelTransform = scale * rotation * translation;
	}
}