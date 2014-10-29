#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>

// Helper functions
////////////////////////////////////
b2Vec2 umathToBox2D(const pmath::Vec2& vec);
pmath::Vec2 box2DToUmath(const b2Vec2& vec);
////////////////////////////////////

using namespace uth;

Rigidbody::Rigidbody(PhysicsWorld& world, const COLLIDER_TYPE collider, const std::string& name)
	: Component(name),
	  m_world(world.GetBox2dWorldObject()),
	  m_collider(collider)
{
	defaults();
}

Rigidbody::Rigidbody(PhysicsWorld& world, const COLLIDER_TYPE collider, const pmath::Vec2& size, const std::string& name)
	: Component(name),
	  m_world(world.GetBox2dWorldObject()),
	  m_collider(collider),
	  m_size(size)
{
	defaults();
}


Rigidbody::~Rigidbody()
{
    if (m_body != nullptr && !m_world.expired())
        m_world.lock()->DestroyBody(m_body);
}


// Public

void Rigidbody::Init()
{
	init();
}

void Rigidbody::Update(float)
{
	const float angDegrees = GetAngle();
	parent->transform.SetRotation(angDegrees);

	b2Vec2 pos = m_body->GetPosition();
	pmath::Vec2 tpos(pos.x, pos.y);
	tpos *= PIXELS_PER_METER;
	parent->transform.SetPosition(tpos);
}


// Apply forces

void Rigidbody::ApplyForce(const pmath::Vec2& force)
{
	m_body->ApplyForceToCenter(umathToBox2D(force), true);
}

void Rigidbody::ApplyForce(const pmath::Vec2& force, const pmath::Vec2& point)
{
	b2Vec2 p = umathToBox2D(point / PIXELS_PER_METER) + m_body->GetPosition();
	m_body->ApplyForce(umathToBox2D(force), p, true);
}

void Rigidbody::ApplyImpulse(const pmath::Vec2& impulse)
{
	m_body->ApplyLinearImpulse(umathToBox2D(impulse), m_body->GetPosition(), true);
}

void Rigidbody::ApplyImpulse(const pmath::Vec2& impulse, const pmath::Vec2& point)
{
	b2Vec2 p = umathToBox2D(point / PIXELS_PER_METER) + m_body->GetPosition();
	m_body->ApplyLinearImpulse(umathToBox2D(impulse), p, true);
}

void Rigidbody::ApplyTorque(const float torque)
{
	m_body->ApplyTorque(-torque, true);
}


// Setters/Getters

void Rigidbody::SetVelocity(const pmath::Vec2& velocity)
{
	m_body->SetLinearVelocity(umathToBox2D(velocity));
}

const pmath::Vec2 Rigidbody::GetVelocity() const
{
	return box2DToUmath(m_body->GetLinearVelocity());
}

void Rigidbody::SetAngularVelocity(float velocity)
{
	m_body->SetAngularVelocity(velocity);
}

float Rigidbody::GetAngularVelocity() const
{
	return m_body->GetAngularVelocity();
}

void Rigidbody::SetSize(const pmath::Vec2& size)
{
	SetUnitSize(size / PIXELS_PER_METER);
}

void Rigidbody::SetUnitSize(const pmath::Vec2& size)
{
	// This function is kinda ugly but what can you do

	if(m_body->GetFixtureList()->GetType() != b2Shape::e_polygon)
	{
		WriteWarning("Calling SetSize(vec2 size) on a ball. Size not updated");
		return;
	}

	// Remove original fixture
	m_body->DestroyFixture(m_body->GetFixtureList());

	//WriteLog("x: %f,y: %f\n", size.x, size.y);

	b2PolygonShape box;
	box.SetAsBox(size.x, size.y);
	m_fixtureDef.shape = &box;
	m_body->CreateFixture(&m_fixtureDef);
	m_size = size;
}

void Rigidbody::SetSize(const float radius)
{
	SetUnitSize(radius / PIXELS_PER_METER);
}

void Rigidbody::SetUnitSize(const float radius)
{
	// This might be even more ugly

	if(m_fixtureDef.shape->GetType() != b2Shape::e_circle)
	{
		WriteWarning("Calling SetSize(float radius) on a box. Size not updated");
		return;
	}

	// Remove original fixture
	m_body->DestroyFixture(m_body->GetFixtureList());

	b2CircleShape circle;
	circle.m_radius = radius;
	m_fixtureDef.shape = &circle;
	m_body->CreateFixture(&m_fixtureDef);
	m_size.x = radius*2;
	m_size.y = radius*2;
}

const pmath::Vec2 Rigidbody::GetSize()
{
	return m_size * PIXELS_PER_METER;
}

const pmath::Vec2 Rigidbody::GetUnitSize()
{
	return m_size;
}

void Rigidbody::SetPosition(const pmath::Vec2& position)
{
	b2Vec2 p = umathToBox2D(position / PIXELS_PER_METER);
	m_body->SetTransform(p, m_body->GetAngle());
}

const pmath::Vec2 Rigidbody::GetPosition()
{
	b2Vec2 pos = m_body->GetPosition();
	pos *= PIXELS_PER_METER;
	return box2DToUmath(pos);
}

void Rigidbody::SetAngle(const float angle)
{
	float ang = -angle * static_cast<float>(pmath::pi) / 180.f;
	m_body->SetTransform(m_body->GetPosition(), ang);
}

float Rigidbody::GetAngle() const
{
	return -m_body->GetAngle() * 180.f / static_cast<float>(pmath::pi);
}

void Rigidbody::Move(const pmath::Vec2& offset)
{
    SetPosition(GetPosition() + offset);
}

void Rigidbody::Rotate(const float angle)
{
    SetAngle(GetAngle() + angle);
}

void Rigidbody::SetFixedRotation(bool value)
{
	m_body->SetFixedRotation(value);
}

void Rigidbody::SetDensity(float density)
{
	m_body->GetFixtureList()->SetDensity(density);
	m_body->ResetMassData();
}

float Rigidbody::GetDensity() const
{
	return m_body->GetFixtureList()->GetDensity();
}

void Rigidbody::SetFriction(float friction)
{
	m_body->GetFixtureList()->SetFriction(friction);
}

float Rigidbody::GetFriction() const
{
	return m_body->GetFixtureList()->GetFriction();
}

void Rigidbody::SetRestitution(float restitution)
{
    m_body->GetFixtureList()->SetRestitution(restitution);
}

float uth::Rigidbody::GetRestitution() const
{
    return m_body->GetFixtureList()->GetRestitution();
}

std::shared_ptr<tinyxml2::XMLNode> uth::Rigidbody::save() const
{
    return std::shared_ptr<tinyxml2::XMLNode>();
}

bool uth::Rigidbody::load(const tinyxml2::XMLNode& doc)
{
    return false;
}

void Rigidbody::SetActive(bool value)
{
	m_body->SetActive(value);
	m_active = value;
}

const bool Rigidbody::IsAwake() const
{
	return m_body->IsAwake();
}

void Rigidbody::SetBullet(bool value)
{
	m_body->SetBullet(value);
}

const bool Rigidbody::IsBullet() const
{
	return m_body->IsBullet();
}

void Rigidbody::SetKinematic(bool value)
{
	value ? m_body->SetType(b2_kinematicBody) : m_body->SetType(b2_dynamicBody);
}

void Rigidbody::SetPhysicsGroup(const short index)
{
    auto filter = m_body->GetFixtureList()->GetFilterData();

    filter.groupIndex = index;

    m_body->GetFixtureList()->SetFilterData(filter);
}

short Rigidbody::GetPhysicsGroup() const
{
    return m_body->GetFixtureList()->GetFilterData().groupIndex;
}

void Rigidbody::SetPhysicsCategory(const Physics::Category category)
{
    auto filter = m_body->GetFixtureList()->GetFilterData();

    filter.categoryBits = static_cast<short>(category);

    m_body->GetFixtureList()->SetFilterData(filter);
}

Physics::Category Rigidbody::GetPhysicsCategory() const
{
    return static_cast<Physics::Category>(m_body->GetFixtureList()->
        GetFilterData().categoryBits);
}


void Rigidbody::SetPhysicsMask(const short mask)
{
    auto filter = m_body->GetFixtureList()->GetFilterData();

    filter.maskBits = mask;

    m_body->GetFixtureList()->SetFilterData(filter);
}

short Rigidbody::GetPhysicsMask() const
{
    return m_body->GetFixtureList()->GetFilterData().maskBits;
}

// Private

void Rigidbody::defaults()
{
	m_body = nullptr;
}

void Rigidbody::init()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	pmath::Vec2 pos = parent->transform.GetPosition();
	pos /= PIXELS_PER_METER;
	bodyDef.position.Set(pos.x, pos.y);

	m_body = m_world.lock()->CreateBody(&bodyDef);
	m_body->SetUserData(parent);

    if (!(m_size.lengthSquared() > 0))
    {
        m_size = parent->transform.GetSize();
        m_size.scale(parent->transform.GetScale());
    }

	m_size /= PIXELS_PER_METER;

	switch(m_collider)
	{
	case COLLIDER_BOX:
		{
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(m_size.x/2, m_size.y/2);

		m_fixtureDef.shape = &dynamicBox;
		m_fixtureDef.density = 1.0f;
		m_fixtureDef.friction = 0.3f;
		m_body->CreateFixture(&m_fixtureDef);
		}
		break;
	case COLLIDER_BALL:
		{
		b2CircleShape circleShape;
		circleShape.m_radius = m_size.x/2;

		m_fixtureDef.shape = &circleShape;
		m_fixtureDef.density = 1.0f;
		m_fixtureDef.friction = 0.3f;
		m_body->CreateFixture(&m_fixtureDef);
		}
		break;
	default:
		WriteError("Collider type undefined\nThis is probably bad");
		break;
	}
}



b2Vec2 umathToBox2D(const pmath::Vec2& vec)
{
	return b2Vec2(vec.x, vec.y);
}

pmath::Vec2 box2DToUmath(const b2Vec2& vec)
{
	return pmath::Vec2(vec.x, vec.y);
}