#include <UtH/Engine/Transform.hpp>
#include <UtH/Engine/GameObject.hpp>

#include <cmath>

using namespace uth;
using namespace pmath;

Transform::Transform(const std::string& name)
	: Component(name),
	  m_position(0, 0),
	  m_size(1, 1),
	  m_scale(1, 1),
      m_origin(0, 0),
	  m_angle(0),
	  m_transformNeedsUpdate(true)
{ }
Transform::~Transform()
{ }

// Public

void Transform::Move(const pmath::Vec2& offset)
{
    m_position += offset;
	m_transformNeedsUpdate = true;
}
void Transform::Move(const float offsetX, const float offsetY)
{
	Move(pmath::Vec2(offsetX, offsetY));
}

void Transform::SetPosition(const pmath::Vec2& position)
{
    this->m_position = position;
	m_transformNeedsUpdate = true;
}
void Transform::SetPosition(const float posX, const float posY)
{
	SetPosition(pmath::Vec2(posX, posY));
}
const pmath::Vec2& Transform::GetPosition() const
{
    return m_position;
}

void Transform::SetSize(const pmath::Vec2& size)
{
    this->m_size = size;
	m_transformNeedsUpdate = true;
}
void Transform::SetSize(const float width, const float height)
{
	SetSize(pmath::Vec2(width, height));
}
const pmath::Vec2& Transform::GetSize() const
{
    return m_size;
}


void Transform::SetOrigin(const pmath::Vec2& origin)
{
    this->m_origin = origin;
	m_transformNeedsUpdate = true;
}
void Transform::SetOrigin(const int originPoint)
{
	switch (originPoint)
	{
	case Origin::Point::BottomLeft:
        SetOrigin(Vec2(m_size.x * -0.5f, m_size.y * 0.5f));
		break;
	case Origin::Point::BottomCenter:
        SetOrigin(Vec2(0.0f, m_size.y * 0.5f));
		break;
	case Origin::Point::BottomRight:
        SetOrigin(Vec2(m_size.x * 0.5f, m_size.y * 0.5f));
		break;
	case Origin::Point::MidLeft:
        SetOrigin(Vec2(m_size.x * -0.5f, 0.f));
		break;
	case Origin::Point::MidRight:
        SetOrigin(Vec2(m_size.x * 0.5f, 0.f));
		break;
	case Origin::Point::TopLeft:
        SetOrigin(Vec2(m_size.x * -0.5f, m_size.y * -0.5f));
		break;
	case Origin::Point::TopCenter:
        SetOrigin(Vec2(0.0f, m_size.y * -0.5f));
		break;
	case Origin::Point::TopRight:
        SetOrigin(Vec2(m_size.x * 0.5f, m_size.y * -0.5f));
		break;
	case Origin::Point::Center:
	default:
		SetOrigin(Vec2());
		break;
	}
}
const pmath::Vec2& Transform::GetOrigin() const
{
	return m_origin;
}

void Transform::SetScale(const pmath::Vec2& scale)
{
	this->m_scale = scale;
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
    return m_scale;
}

void Transform::SetRotation(const float degrees)
{
    this->m_angle = degrees;
	m_transformNeedsUpdate = true;
}
const float Transform::GetRotation() const
{
    return m_angle;
}
void Transform::Rotate(const float degrees)
{
    this->m_angle += degrees;
	m_transformNeedsUpdate = true;
}

pmath::Rect Transform::GetBounds() const
{
    Vec2 scaled = m_size;
    scaled.scale(m_scale);
    Vec2 sOrig = m_origin;
    sOrig.scale(m_scale);

    return pmath::Rect((m_position - sOrig) - scaled / 2.f, scaled);
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

    m_modelTransform = pmath::Mat4();

    if (m_position != pmath::Vec2(0.f, 0.f))
        m_modelTransform = m_modelTransform * pmath::Mat4::createTranslation(m_position.x, m_position.y, 0.f);

    if (m_angle != 0.f)
        m_modelTransform = m_modelTransform * pmath::Mat4::createRotationZ(m_angle);

    if (m_scale != pmath::Vec2(1.f, 1.f))
        m_modelTransform = m_modelTransform * pmath::Mat4::createScaling(m_scale.x, m_scale.y, 1.f);
    
    if (m_origin != pmath::Vec2(0.f, 0.f))
        m_modelTransform = m_modelTransform * pmath::Mat4::createTranslation(-m_origin.x, -m_origin.y, 0.f);

	m_transformNeedsUpdate = false;
}
