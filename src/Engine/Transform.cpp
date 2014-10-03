#include <UtH/Engine/Transform.hpp>
#include <UtH/Engine/GameObject.hpp>

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
const pmath::Vec2& Transform::GetPosition() const
{
    return m_position;
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
    pmath::Vec2 scaled = m_size;
    scaled.scale(m_scale);
    pmath::Vec2 sOrig = m_origin;
    sOrig.scale(m_scale);

    return pmath::Rect((m_position - sOrig) - scaled / 2.f, scaled);
}

pmath::Rect Transform::GetTransformedBounds() const
{
    const pmath::Vec2 topLeft(m_position - m_size / 2.f - m_origin);

    const auto& tf = GetTransform();

    std::array<pmath::Vec2, 4> points =
    { {
        pmath::Vec2(topLeft),
        pmath::Vec2(topLeft.x, topLeft.y + m_size.y),
        pmath::Vec2(topLeft + m_size),
        pmath::Vec2(topLeft.x + m_size.x, topLeft.y)
        } };

    float left = 0.f,
          right = 0.f,
          bottom = 0.f,
          top = 0.f;

    for (auto& i : points)
    {
        // Add transform matrix first
        i *= tf;

        if (i.x < left)
            left = i.x;
        else if (i.x > right)
            right = i.x;

        if (i.y < top)
            top = i.y;
        else if (i.y > bottom)
            bottom = i.y;
    }

    return pmath::Rect(left, top, right - left, bottom - top);
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

	if (parent && (parent->HasParent<GameObject>()))
	{
		m_combinedTransform = parent->Parent<GameObject>()->transform.GetTransform() *
			m_modelTransform;

		return m_combinedTransform;
	}
	else if (parent && parent->HasParent<Layer>())
	{
		m_combinedTransform = parent->Parent<Layer>()->transform.GetTransform() *
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
