#include <UtH/Engine/Rigidbody.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

Rigidbody::Rigidbody(b2World* world, const std::string name)
	: Component(name),
	  m_world(world),
	  m_isInitialized(false)
{ }

Rigidbody::~Rigidbody()
{ }


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

void Rigidbody::init()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	umath::vector2 pos = parent->transform.position;
	pos /= PIXELS_PER_METER;
	bodyDef.position.Set(pos.x, pos.y);

	m_body = m_world->CreateBody(&bodyDef);

	umath::vector2 size = parent->transform.size;
	size /= PIXELS_PER_METER;

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(size.x/2, size.y/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	m_body->CreateFixture(&fixtureDef);

	m_isInitialized = true;
}