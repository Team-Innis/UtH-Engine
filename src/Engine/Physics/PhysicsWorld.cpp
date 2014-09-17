#include <UtH/Engine/Physics/PhysicsWorld.hpp>

using namespace uth;

PhysicsWorld::PhysicsWorld(const float x, const float y,
    const PhysicsSettings& settings)
    : m_world(new b2World(b2Vec2(x, y))),
    m_settings(settings)
{ }

PhysicsWorld::PhysicsWorld(const pmath::Vec2& gravity,
    const PhysicsSettings& settings)
    : PhysicsWorld(gravity.x, gravity.y, settings)
{ }

PhysicsWorld::PhysicsWorld()
    : PhysicsWorld(0, 0)
{ }

void PhysicsWorld::SetGravity(const float x, const float y)
{
    m_world->SetGravity(b2Vec2(x, y));
}

void PhysicsWorld::SetGravity(const pmath::Vec2& gravity)
{
    SetGravity(gravity.x, gravity.y);
}

const pmath::Vec2 PhysicsWorld::GetGravity() const
{
    pmath::Vec2 out;
    b2Vec2 g = m_world->GetGravity();
    out.x = g.x;
    out.y = g.y;

    return out;
}

void PhysicsWorld::SetContactListener(PhysicsContactListener* contactListener)
{
    m_world->SetContactListener(contactListener);
}

void PhysicsWorld::Update()
{
    m_world->Step(m_settings.timeStep, m_settings.velocityIterations,
        m_settings.positionIterations);
}

void PhysicsWorld::SetSettings(const PhysicsSettings& settings)
{
    m_settings = settings;
}

PhysicsSettings& PhysicsWorld::GetSettings()
{
    return m_settings;
}

std::shared_ptr<b2World> PhysicsWorld::GetBox2dWorldObject()
{
    return m_world;
}
