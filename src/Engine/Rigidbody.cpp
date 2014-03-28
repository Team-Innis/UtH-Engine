#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>

// Helper functions
////////////////////////////////////
b2Vec2 umathToBox2D(const umath::vector2& vec);
umath::vector2 box2DToUmath(const b2Vec2& vec);
////////////////////////////////////

using namespace uth;

Rigidbody::Rigidbody(b2World* world, const COLLIDER_TYPE collider, const std::string& name)
	: Component(name),
	  m_world(world),
	  m_collider(collider)
{
	defaults();
}

Rigidbody::Rigidbody(b2World* world, const COLLIDER_TYPE collider, const umath::vector2& size, const std::string& name)
	: Component(name),
	  m_world(world),
	  m_collider(collider),
	  m_size(size)
{
	defaults();
}


Rigidbody::~Rigidbody()
{
	if(m_body != nullptr)
		m_world->DestroyBody(m_body);
}


// Public

void Rigidbody::Init()
{
	init();
}

void Rigidbody::Update(float dt)
{
		float angDegrees = GetAngle();
		parent->transform.SetRotation(angDegrees);

		b2Vec2 pos = m_body->GetPosition();
		umath::vector2 tpos(pos.x, pos.y);
		tpos *= PIXELS_PER_METER;
		parent->transform.SetPosition(tpos);
}


// Apply forces

void Rigidbody::ApplyForce(const umath::vector2& force)
{
	m_body->ApplyForceToCenter(umathToBox2D(force), true);
}

void Rigidbody::ApplyForce(const umath::vector2& force, const umath::vector2& point)
{
	b2Vec2 p = umathToBox2D(point / PIXELS_PER_METER) + m_body->GetPosition();
	m_body->ApplyForce(umathToBox2D(force), p, true);
}

void Rigidbody::ApplyImpulse(const umath::vector2& impulse)
{
	m_body->ApplyLinearImpulse(umathToBox2D(impulse), m_body->GetPosition(), true);
}

void Rigidbody::ApplyImpulse(const umath::vector2& impulse, const umath::vector2& point)
{
	b2Vec2 p = umathToBox2D(point / PIXELS_PER_METER) + m_body->GetPosition();
	m_body->ApplyLinearImpulse(umathToBox2D(impulse), p, true);
}

void Rigidbody::ApplyTorque(const float torque)
{
	m_body->ApplyTorque(-torque, true);
}


// Setters/Getters

void Rigidbody::SetVelocity(const umath::vector2& velocity)
{
	m_body->SetLinearVelocity(umathToBox2D(velocity));
}

const umath::vector2 Rigidbody::GetVelocity() const
{
	return box2DToUmath(m_body->GetLinearVelocity());
}

void Rigidbody::SetSize(const umath::vector2& size)
{
	SetUnitSize(size / PIXELS_PER_METER);
}

void Rigidbody::SetUnitSize(const umath::vector2& size)
{
	// This function is kinda ugly but what can you do

	if(m_body->GetFixtureList()->GetType() != b2Shape::e_polygon)
	{
		WriteLog("WARNING: Calling SetSize(vec2 size) on a ball. Size not updated\n");
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
		WriteLog("WARNING: Calling SetSize(float radius) on a box. Size not updated\n");
		return;
	}

	// Remove original fixture
	m_body->DestroyFixture(m_body->GetFixtureList());


	float curAng = m_body->GetAngle();
	
	b2CircleShape circle;
	circle.m_radius = radius;
	m_fixtureDef.shape = &circle;
	m_body->CreateFixture(&m_fixtureDef);
	m_size.x = radius*2;
	m_size.y = radius*2;
}

const umath::vector2 Rigidbody::GetSize()
{
	return m_size * PIXELS_PER_METER;
}

const umath::vector2 Rigidbody::GetUnitSize()
{
	return m_size;
}

void Rigidbody::SetPosition(const umath::vector2& position)
{
	b2Vec2 p = umathToBox2D(position / PIXELS_PER_METER);
	m_body->SetTransform(p, m_body->GetAngle());
}

const umath::vector2 Rigidbody::GetPosition()
{
	b2Vec2 pos = m_body->GetPosition();
	pos *= PIXELS_PER_METER;
	return box2DToUmath(pos);
}

void Rigidbody::SetAngle(const float angle)
{
	float ang = -angle * PI / 180.f;
	m_body->SetTransform(m_body->GetPosition(), ang);
}

const float Rigidbody::GetAngle()
{
	return -m_body->GetAngle() * 180.f / PI;
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


// Private

void Rigidbody::defaults()
{
	m_body = nullptr;
}

void Rigidbody::init()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	umath::vector2 pos = parent->transform.position;
	pos /= PIXELS_PER_METER;
	bodyDef.position.Set(pos.x, pos.y);

	m_body = m_world->CreateBody(&bodyDef);
	
	if(!(m_size.getLenght() > 0))
		m_size = parent->transform.size;


	m_size /= PIXELS_PER_METER;

	// TODO: remove pointless userdata

	switch(m_collider)
	{
	case COLLIDER_BOX:
		{
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(m_size.x/2, m_size.y/2);

		m_fixtureDef.userData = "Box";
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

		m_fixtureDef.userData = "Ball";
		m_fixtureDef.shape = &circleShape;
		m_fixtureDef.density = 1.0f;
		m_fixtureDef.friction = 0.3f;
		m_body->CreateFixture(&m_fixtureDef);
		}
		break;
	default:
		WriteLog("Collider type undefined\nThis is probably bad\n");
		break;
	}
}

b2Vec2 umathToBox2D(const umath::vector2& vec)
{
	return b2Vec2(vec.x, vec.y);
}

umath::vector2 box2DToUmath(const b2Vec2& vec)
{
	return umath::vector2(vec.x, vec.y);
}

