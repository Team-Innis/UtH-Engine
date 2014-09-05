#include <UtH/Engine/Transform.hpp>
#include <UtH/Engine/GameObject.hpp>

#include <cmath>

using namespace uth;
using namespace pmath;

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

void Transform::Move(const pmath::Vec2& offset)
{
	position += offset;
	m_transformNeedsUpdate = true;
}
void Transform::Move(const float offsetX, const float offsetY)
{
	Move(pmath::Vec2(offsetX, offsetY));
}

void Transform::SetPosition(const pmath::Vec2& position)
{
	this->position = position;
	m_transformNeedsUpdate = true;
}
void Transform::SetPosition(const float posX, const float posY)
{
	SetPosition(pmath::Vec2(posX, posY));
}
const pmath::Vec2& Transform::GetPosition() const
{
	return position;
}

void Transform::SetSize(const pmath::Vec2& size)
{
	this->size = size;
	m_transformNeedsUpdate = true;
}
void Transform::SetSize(const float width, const float height)
{
	SetSize(pmath::Vec2(width, height));
}
const pmath::Vec2& Transform::GetSize() const
{
	return size;
}


void Transform::SetOrigin(const pmath::Vec2& origin)
{
	this->origin = origin;
	m_transformNeedsUpdate = true;
}
void Transform::SetOrigin(const int originPoint)
{
	switch (originPoint)
	{
	case Origin::Point::BottomLeft:
		SetOrigin(Vec2(size.x * -0.5f,size.y * 0.5f));
		break;
	case Origin::Point::BottomCenter:
		SetOrigin(Vec2(0.0f, size.y * 0.5f));
		break;
	case Origin::Point::BottomRight:
		SetOrigin(Vec2(size.x * 0.5f, size.y * 0.5f));
		break;
	case Origin::Point::MidLeft:
		SetOrigin(Vec2(size.x * -0.5f, 0.f));
		break;
	case Origin::Point::MidRight:
		SetOrigin(Vec2(size.x * 0.5f, 0.f));
		break;
	case Origin::Point::TopLeft:
		SetOrigin(Vec2(size.x * -0.5f, size.y * -0.5f));
		break;
	case Origin::Point::TopCenter:
		SetOrigin(Vec2(0.0f, size.y * -0.5f));
		break;
	case Origin::Point::TopRight:
		SetOrigin(Vec2(size.x * 0.5f, size.y * -0.5f));
		break;
	case Origin::Point::Center:
	default:
		SetOrigin(Vec2());
		break;
	}
}
const pmath::Vec2& Transform::GetOrigin() const
{
	return origin;
}

void Transform::SetScale(const pmath::Vec2& scale)
{
	this->scale = scale;
	m_transformNeedsUpdate = true;
}
void Transform::SetScale(const float xScale, const float yScale)
{
	SetScale(pmath::Vec2(xScale, yScale));
}
void Transform::SetScale(const float scale)
{
	SetScale(pmath::Vec2(scale, scale));
}
const pmath::Vec2& Transform::GetScale() const
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

void Transform::SetTransform(const pmath::Mat4& modelTransform)
{
	m_modelTransform = modelTransform;
}

void Transform::AddTransform(const pmath::Mat4& modelTransform)
{
	m_transformNeedsUpdate = true;

	m_modelTransform = m_modelTransform * modelTransform;
}
const pmath::Mat4& Transform::GetTransform()
{
	updateTransform();

	if(parent != nullptr && parent->parent != nullptr)
		AddTransform(parent->parent->transform.GetTransform());

	return m_modelTransform;
}

// Private

void Transform::updateTransform()
{
	if (!m_transformNeedsUpdate)
		return;

	const float ang = -angle * static_cast<float>(pi) / 180.f;
	const float cosine = std::cos(ang);
	const float sine = std::sin(ang);

	const pmath::Mat4 orig(
		1.0f,   0,      0,      -origin.x,
		0,      1.0f,   0,      -origin.y,
		0,      0,      1.0f,   0,
		0,      0,      0,      1.0f
		);

	const pmath::Mat4 rotation(
		cosine, -sine,   0,      0,
		sine,   cosine, 0,      0,
		0,      0,      1.0f,   0,
		0,      0,      0,      1.0f
		);

	const pmath::Mat4 scaleMatrix(
		scale.x,   0,                  0,      0,
		0,                  scale.y,   0,      0,
		0,                  0,                  1.0f,   0,
		0,                  0,                  0,      1.0f
		);

	const pmath::Mat4 translation(
		1.0f,   0,      0,      position.x,
		0,      1.0f,   0,      position.y,
		0,      0,      1.0f,   0,
		0,      0,      0,      1.0f
		);

	m_modelTransform = translation * rotation * scaleMatrix * orig;
	m_transformNeedsUpdate = false;
}