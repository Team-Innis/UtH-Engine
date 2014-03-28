#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>

// Helper functions
////////////////////////////////////
b2Vec2 umathToBox2D(const umath::vector2& vec);
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
	if(!m_isInitialized && parent->transform.GetSize().getLenght() > sqrt(2.0))
		init();

	if(IsInitialized())
	{
		b2Vec2 pos = m_body->GetPosition();

		float angDegrees = -m_body->GetAngle() * 180.f / PI;
		parent->transform.SetRotation(angDegrees);

		umath::vector2 tpos(pos.x, pos.y);
		tpos *= PIXELS_PER_METER;

		WriteLog("x: %f, y: %f, angle: %f\n", tpos.x, tpos.y, angDegrees);
		parent->transform.SetPosition(tpos);
	}
}


const bool Rigidbody::IsInitialized() const
{
	return m_isInitialized;
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

// Private

void Rigidbody::defaults()
{
	m_isInitialized = false;
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

	switch(m_collider)
	{
	case COLLIDER_BOX:
		{
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(m_size.x/2, m_size.y/2);

		b2FixtureDef fixtureDef;
		fixtureDef.userData = "Laatikko";
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		m_body->CreateFixture(&fixtureDef);
		}
		break;
	case COLLIDER_BALL:
		{
		b2CircleShape circleShape;
		circleShape.m_radius = m_size.x/2;

		b2FixtureDef fixtureDef;
		fixtureDef.userData = "Pallo";
		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		m_body->CreateFixture(&fixtureDef);
		}
		break;
	default:
		WriteLog("Collider type undefined\nThis is probably bad\n");
		break;
	}
	m_isInitialized = true;
}

b2Vec2 umathToBox2D(const umath::vector2& vec)
{
	return b2Vec2(vec.x, vec.y);
}
