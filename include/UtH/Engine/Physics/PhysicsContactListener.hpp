#ifndef PHYSICSCONTACTLISTENER_H
#define PHYSICSCONTACTLISTENER_H

#include <functional>
#include <Box2D/Box2D.h>
#include <UtH/Engine/GameObject.hpp>

namespace uth
{
	class PhysicsContactListener : public b2ContactListener
	{
	public:

		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

		std::function<void(b2Contact* contact, GameObject* a, GameObject* b)> onBeginContact = nullptr;
		std::function<void(b2Contact* contact, const b2Manifold* oldManifold, GameObject* a, GameObject* b)> onPreSolve = nullptr;
		std::function<void(b2Contact* contact, const b2ContactImpulse* impulse, GameObject* a, GameObject* b)> onPostSolve = nullptr;
		std::function<void(b2Contact* contact, GameObject* a, GameObject* b)> onEndContact = nullptr;

	};
}

#endif