#include <UtH/Engine/Physics/PhysicsContactListener.hpp>
#include <UtH/Platform/Debug.hpp>

using namespace uth;

void PhysicsContactListener::BeginContact(b2Contact* contact)
{
	if (onBeginContact)
		onBeginContact(contact, static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData()));
}

void PhysicsContactListener::EndContact(b2Contact* contact)
{
	if (onEndContact)
		onEndContact(contact, static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData()));
}

void PhysicsContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	if (onPreSolve)
		onPreSolve(contact, oldManifold, static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData()));
}

void PhysicsContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	if (onPostSolve)
		onPostSolve(contact, impulse, static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData()),
		static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData()));
}