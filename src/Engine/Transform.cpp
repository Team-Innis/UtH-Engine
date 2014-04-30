#include <UtH/Engine/Transform.hpp>
#include <cmath>

using namespace uth;
using namespace umath;

Transform::Transform(const std::string& name)
	: Component(name),
	  position(0, 0),
	  size(1, 1),
	  scale(1, 1),
      origin(0,0),
	  angle(0),
	  depth(0),
	  m_transformNeedsUpdate(true)
{ }
Transform::~Transform()
{ }

// Public

void Transform::Move(const umath::vector2& offset)
{
	position += offset;
	m_transformNeedsUpdate = true;
}
void Transform::Move(const float offsetX, const float offsetY)
{
	Move(umath::vector2(offsetX, offsetY));
}

void Transform::SetPosition(const umath::vector2& position)
{
	this->position = position;
	m_transformNeedsUpdate = true;
}
void Transform::SetPosition(const float posX, const float posY)
{
	SetPosition(umath::vector2(posX, posY));
}
const umath::vector2& Transform::GetPosition() const
{
	return position;
}

void Transform::SetSize(const umath::vector2& size)
{
	this->size = size;
	m_transformNeedsUpdate = true;
}
void Transform::SetSize(const float width, const float height)
{
	SetSize(umath::vector2(width, height));
}
const umath::vector2& Transform::GetSize() const
{
	return size;
}


void Transform::SetOrigin(const umath::vector2& origin)
{
	this->origin = origin;
	m_transformNeedsUpdate = true;
}
void Transform::SetOrigin(const Origin::Point origin)
{
    switch (origin)
    {
    case Origin::Point::BottomLeft:
        SetOrigin(vector2(size.x * -0.5f,size.y * 0.5f));
        break;
    case Origin::Point::BottomCenter:
        SetOrigin(vector2(0.0f,size.y * 0.5f));
        break;
    case Origin::Point::BottomRight:
        SetOrigin(vector2(size.x * 0.5f,size.y * 0.5f));
        break;
    case Origin::Point::MidLeft:
        SetOrigin(vector2(size.x * -0.5f,0.f));
        break;
    case Origin::Point::MidRight:
        SetOrigin(vector2(size.x * 0.5f,0.f));
        break;
    case Origin::Point::TopLeft:
        SetOrigin(vector2(size.x * -0.5f,size.y * -0.5f));
        break;
    case Origin::Point::TopCenter:
        SetOrigin(vector2(0.0f,size.y * -0.5f));
        break;
    case Origin::Point::TopRight:
        SetOrigin(vector2(size.x * 0.5f,size.y * -0.5f));
        break;
    case Origin::Point::Center:
    default:
        SetOrigin(vector2());
        break;
    }
}
const umath::vector2& Transform::GetOrigin() const
{
	return origin;
}

void Transform::SetScale(const umath::vector2& scale)
{
	this->scale = scale;
	m_transformNeedsUpdate = true;
}
void Transform::SetScale(const float xScale, const float yScale)
{
	SetScale(umath::vector2(xScale, yScale));
}
void Transform::SetScale(const float scale)
{
	SetScale(umath::vector2(scale, scale));
}
const umath::vector2& Transform::GetScale() const
{
	return scale;
}

void Transform::SetRotation(const float degrees)
{
	this->angle = degrees;
	m_transformNeedsUpdate = true;
}
const float Transform::GetRotation() const
{
	return angle;
}
void Transform::Rotate(const float degrees)
{ 
	this->angle += degrees;
	m_transformNeedsUpdate = true;
}

void Transform::SetDepth(const float depth)
{
	this->depth = depth;
	m_transformNeedsUpdate = true;
}
const float Transform::GetDepth() const
{
	return depth;
}

void Transform::SetTransform(const umath::matrix4& modelTransform)
{
	m_modelTransform = modelTransform;
}

void Transform::AddTransform(const umath::matrix4& modelTransform)
{
	m_transformNeedsUpdate = true;

	m_modelTransform = m_modelTransform * modelTransform;
}
const umath::matrix4& Transform::GetTransform()
{
	updateTransform();

	return m_modelTransform;
}

// Private

void Transform::updateTransform()
{
    if (!m_transformNeedsUpdate)
        return;

	const float ang = -angle * PI / 180.f;
	const float cosine = std::cos(ang);
	const float sine = std::sin(ang);
    
    const umath::matrix4 orig(
        1.0f,   0,      0,      -origin.x/size.x,
        0,      1.0f,   0,      -origin.y/size.y,
        0,      0,      1.0f,   0,
        0,      0,      0,      1.0f
        );

    const umath::matrix4 rotation(
        cosine, -sine,   0,      0,
        sine,   cosine, 0,      0,
        0,      0,      1.0f,   0,
        0,      0,      0,      1.0f
        );

    const umath::matrix4 scaleMatrix(
        size.x * scale.x,   0,                  0,      0,
        0,                  size.y * scale.y,   0,      0,
        0,                  0,                  1.0f,   0,
        0,                  0,                  0,      1.0f
        );

    const umath::matrix4 translation(
        1.0f,   0,      0,      position.x,
        0,      1.0f,   0,      position.y,
        0,      0,      1.0f,   0,
        0,      0,      0,      1.0f
        );

	m_modelTransform = translation * rotation * scaleMatrix * orig;
	m_transformNeedsUpdate = false;
}