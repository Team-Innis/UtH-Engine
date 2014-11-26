#include <UtH/Engine/Transform.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>

#include <cmath>
#include <array>

using namespace uth;

Transform::Transform(Object* p)
	: parent(p),
	  m_position(0, 0),
	  m_size(0, 0),
	  m_scale(1, 1),
      m_origin(0, 0),
	  m_angle(0),
	  m_transformNeedsUpdate(true)
{ }
Transform::~Transform()
{

}

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
void uth::Transform::SetGlobalPosition(const pmath::Vec2& position)
{
    // Updating the transform is required
    // (will most likely break everything if not called)
    updateTransform();
    const auto transform = GetTransform()*m_modelTransform.inverse();

    SetPosition(transform.inverse() * position);
}
void uth::Transform::SetGlobalPosition(const float posX, const float posY)
{
    SetGlobalPosition(pmath::Vec2(posX, posY));
}
const pmath::Vec2& Transform::GetPosition() const
{
    return m_position;
}
const pmath::Vec2 uth::Transform::GetGlobalPosition() const
{
    const auto& transform = GetTransform();
    return pmath::Vec2(transform[0][3], transform[1][3]);
}

void Transform::SetSize(const pmath::Vec2& size)
{
	ScaleToSize(size.x, size.y);
}
void Transform::SetSize(const float width, const float height)
{
	ScaleToSize(width, height);
}
void Transform::ScaleToSize(const pmath::Vec2& size)
{
	SetSize(size.x, size.y);
}
void Transform::ScaleToSize(const float width, const float height)
{
	SetScale(width / m_size.x, height / m_size.y);
	m_transformNeedsUpdate = true;
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
    using namespace pmath;

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
void uth::Transform::SetGlobalScale(const pmath::Vec2& scale)
{
    // TODO: Implement this
}
void uth::Transform::SetGlobalScale(const float xScale, const float yScale)
{
    SetGlobalScale(pmath::Vec2(xScale, yScale));
}
void uth::Transform::SetGlobalScale(const float scale)
{
    SetGlobalScale(scale, scale);
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
void uth::Transform::SetGlobalRotation(const float degrees)
{
    // TODO: Implement this
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

pmath::Rect Transform::GetLocalBounds() const
{
    pmath::Vec2 scaled = m_size;
    scaled.scale(m_scale);
    pmath::Vec2 sOrig = m_origin;
    sOrig.scale(m_scale);

    return pmath::Rect((m_position - sOrig) - scaled / 2.f, scaled);
}

pmath::Rect Transform::GetGlobalBounds() const
{
    const auto& tf = GetTransform();

    const pmath::Vec2 size
    {
        m_size.x * pmath::abs(tf[0][0]) + m_size.y * pmath::abs(tf[1][0]),
        m_size.x * pmath::abs(tf[0][1]) + m_size.y * pmath::abs(tf[1][1])
    };

    pmath::Vec2 topLeft{ tf[0][3], tf[1][3] };
    topLeft -= size / 2;
    const pmath::Vec2 bottomRight = topLeft + size;

    return pmath::Rect(topLeft.x, topLeft.y, bottomRight.x - topLeft.x,
        bottomRight.y - topLeft.y);
}


pmath::Rect Transform::GetBounds() const
{
    Deprecated("Use GetLocalBounds()");
    return GetLocalBounds();
}

pmath::Rect Transform::GetTransformedBounds() const
{
    Deprecated("Use GetGlobalBounds()");
    return GetGlobalBounds();
}

void Transform::SetTransform(const pmath::Mat4& modelTransform)
{
	m_modelTransform = modelTransform;
}

void Transform::AddTransform(const pmath::Mat4& modelTransform)
{
	updateTransform();

	m_modelTransform = m_modelTransform * modelTransform;
}
const pmath::Mat4& Transform::GetTransform() const
{
	updateTransform();

	if (parent && (parent->HasParent<Object>()))
	{
		m_combinedTransform = parent->Parent<Object>()->transform.GetTransform() *
			m_modelTransform;

		return m_combinedTransform;
	}

	return m_modelTransform;
}

// Private

void Transform::setSize(const pmath::Vec2& size)
{
	this->m_size = size;
	m_transformNeedsUpdate = true;
}
void Transform::setSize(const float width, const float height)
{
	setSize(pmath::Vec2(width, height));
}

void Transform::updateTransform() const
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