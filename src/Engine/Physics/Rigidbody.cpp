#include <UtH/Engine/Physics/Rigidbody.hpp>
#include <UtH/Engine/GameObject.hpp>
#include <UtH/Platform/Debug.hpp>

// Helper functions
////////////////////////////////////
b2Vec2 umathToBox2D(const pmath::Vec2& vec);
pmath::Vec2 box2DToUmath(const b2Vec2& vec);
////////////////////////////////////

using namespace uth;

//Rigidbody::Rigidbody()
//    : Component("Rigid body")
//{
//
//}

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

float Rigidbody::GetRestitution() const
{
    return m_body->GetFixtureList()->GetRestitution();
}

rapidjson::Value Rigidbody::save(rapidjson::MemoryPoolAllocator<>& alloc) const
{
    namespace rj = rapidjson;

    rj::Value val = Component::save(alloc);

    val.AddMember("colliderType", static_cast<unsigned int>(m_collider), alloc);
    val.AddMember("size", rj::kArrayType, alloc)["size"]
       .PushBack(m_size.x * PIXELS_PER_METER, alloc)
       .PushBack(m_size.y * PIXELS_PER_METER, alloc);

    // Fixture
    {
        rj::Value& fix = val.AddMember(rj::StringRef("fixture"), rj::kObjectType, alloc)["fixture"];
        
        fix.AddMember(rj::StringRef("filterData"), rj::kArrayType, alloc)["filterData"]
           .PushBack(m_fixtureDef.filter.categoryBits, alloc)
           .PushBack(m_fixtureDef.filter.groupIndex, alloc)
           .PushBack(m_fixtureDef.filter.maskBits, alloc);
        
        fix.AddMember(rj::StringRef("properties"), rj::kArrayType, alloc)["properties"]
           .PushBack(m_fixtureDef.density, alloc)
           .PushBack(m_fixtureDef.friction, alloc)
           .PushBack(m_fixtureDef.isSensor, alloc)
           .PushBack(m_fixtureDef.restitution, alloc);
    }

    // Body
    {
        val.AddMember(rj::StringRef("body"), rj::kArrayType, alloc)["body"]
           .PushBack(m_body->GetAngle(), alloc)
           .PushBack(m_body->GetAngularDamping(), alloc)
           .PushBack(m_body->GetAngularVelocity(), alloc)
           .PushBack(m_body->GetGravityScale(), alloc)
           .PushBack(m_body->GetLinearDamping(), alloc)
           .PushBack(m_body->GetLinearVelocity().x, alloc)
           .PushBack(m_body->GetLinearVelocity().y, alloc)
           .PushBack(m_body->GetPosition().x, alloc)
           .PushBack(m_body->GetPosition().y, alloc)
           .PushBack(m_body->IsActive(), alloc)
           .PushBack(m_body->IsBullet(), alloc)
           .PushBack(m_body->IsFixedRotation(), alloc)
           .PushBack(m_body->IsSleepingAllowed(), alloc)
           .PushBack(m_body->GetType() == b2_kinematicBody, alloc);
    }

    return val;
}

bool Rigidbody::load(const rapidjson::Value& doc)
{
    namespace rj = rapidjson;

    if (!Component::load(doc))
        return false;

    init();

    // Fixture
    {
        const rj::Value& fix = doc["fixture"];

        const rj::Value& filter = fix["filterData"];
        SetPhysicsCategory(static_cast<Physics::Category>(filter[0u].GetUint()));
        SetPhysicsGroup(filter[1].GetUint());
        SetPhysicsMask(filter[2].GetUint());

        const rj::Value& props = fix["properties"];
        SetDensity(props[0u].GetDouble());
        SetFriction(props[1].GetDouble());
        SetTrigger(props[2].GetBool());
        SetRestitution(props[3].GetDouble());
    }

    // Body
    {
        const rj::Value& body = doc["body"];
        SetAngle(body[0u].GetDouble());
        m_body->SetAngularDamping(body[1].GetDouble());
        SetAngularVelocity(body[2].GetDouble());
        m_body->SetGravityScale(body[3].GetDouble());
        m_body->SetLinearDamping(body[4].GetDouble());
        SetVelocity(pmath::Vec2(body[5].GetDouble(), body[6].GetDouble()));
        SetPosition(pmath::Vec2(body[7].GetDouble(), body[8].GetDouble()));
        SetActive(body[9].GetBool());
        SetBullet(body[10].GetBool());
        SetFixedRotation(body[11].GetBool());
        m_body->SetSleepingAllowed(body[12].GetBool());
        SetKinematic(body[13].GetBool());
    }

    return true;
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

void Rigidbody::SetTrigger(bool trigger)
{
    m_body->GetFixtureList()->SetSensor(trigger);
}

bool Rigidbody::IsTrigger() const
{
    return m_body->GetFixtureList()->IsSensor();
}

b2Body* Rigidbody::GetBox2dBody() const
{
    return m_body;
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