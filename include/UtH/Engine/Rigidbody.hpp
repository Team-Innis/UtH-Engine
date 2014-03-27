#pragma once
#ifndef RIGIDBODY_H_UTH
#define RIGIDBODY_H_UTH

#include <UtH/Engine/Component.hpp>
#include <Box2D/Box2D.h>
#include <UtH/Math/Vector.hpp>

namespace uth
{
	enum COLLIDER_TYPE
	{
		COLLIDER_BOX,
		COLLIDER_BALL
	};

	const float PIXELS_PER_METER = 50.f;

	class Rigidbody : public Component
	{
	public:
		// Create a rigidbody with a default box collider
		Rigidbody(b2World* world, const COLLIDER_TYPE collider = COLLIDER_BOX,
			const std::string name = "Rigidbody");
		// Create a rigidibody with a bit more control
		Rigidbody(b2World* world, const COLLIDER_TYPE collider, 
			const umath::vector2& size, const std::string name = "Rigidbody");

		~Rigidbody();

		void Update(float dt);
		// Most other functions will not work untile the object is initialzed
		// This should at most only take a few frames
		bool IsInitialized() const;

		// Sets if the object is active
		// Inactive objects will unaffetec by all physics
		void SetActive(bool value);
		// Is object awake or sleeping
		const bool IsAwake() const;

		// Set the object as a bullet
		// This means the object will have continuous collision detection
		// (like a bullet should have)
		void SetBullet(bool value);
		const bool IsBullet() const;

		// Functions to add all kinds of forces to the object
		// Adding force will wake up the object

		// Applies force to the center of the object
		void ApplyForce(const umath::vector2& force);
		// Applies force to a point on the object (offset from the center of the object)
		// This means applying force to the point (0, 0) is the same as center of object
		// Point is expected to be a pixel offset (not Box2D meter offset)
		void ApplyForce(const umath::vector2& force, const umath::vector2& point);

		// Applies impulse to the center of the object
		void ApplyImpulse(const umath::vector2& impulse);
		// Applies impulse to a point on the object (offset from the center of the object)
		void ApplyImpulse(const umath::vector2& impulse, const umath::vector2& point);

		// Applies torque to the object
		// Positive torque means counter-clockwise rotation
		void ApplyTorque(const float torque);

	private:
		void defaults();
		void init();

		b2Vec2 umathToBox2D(const umath::vector2& vec);

		bool m_isInitialized;

		Rigidbody();

		b2World* m_world;
		b2Body* m_body;
		COLLIDER_TYPE m_collider;
		umath::vector2 m_size;
	};
}

#endif