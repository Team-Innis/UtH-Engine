#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

Rigidbody::Rigidbody(b2World* world, const COLLIDER_TYPE collider, const std::string name)
	: Component(name),
	  m_world(world),
	  m_collider(collider)
{
	defaults();
}

Rigidbody::Rigidbody(b2World* world, const COLLIDER_TYPE collider, const umath::vector2& size, const std::string name)
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

void Rigidbody::Update(float dt)
{
	if(!m_isInitialized && parent->transform.GetSize().getLenght() > sqrt(2.0))
		init();

	if(isInitialized())
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

bool Rigidbody::isInitialized() const
{
	return m_isInitialized;
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
	
	if(!m_size.getLenght() > 0)
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