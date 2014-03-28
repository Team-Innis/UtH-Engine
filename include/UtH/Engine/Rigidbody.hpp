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

	// Conversion from pixels to meters
	const float PIXELS_PER_METER = 50.f;

	class Rigidbody : public Component
	{
	public:
		// Create a rigidbody with a default box collider
		Rigidbody(b2World* world, const COLLIDER_TYPE collider = COLLIDER_BOX,
			const std::string& name = "Rigidbody");
		// Create a rigidibody with a bit more control
		// If creating a ball put diameter in size.x
		Rigidbody(b2World* world, const COLLIDER_TYPE collider, 
			const umath::vector2& size, const std::string& name = "Rigidbody");

		~Rigidbody();

		void Init();
		void Update(float dt);

		// Functions to add all kinds of forces to the object
		// Adding force will wake up the object

		// Applies force to the center of the object
		// Force is usually considered to be in Newtons(N)
		void ApplyForce(const umath::vector2& force);
		// Applies force to a point on the object (offset from the center of the object)
		// This means applying force to the point (0, 0) is the same as center of object
		// Point is expected to be a pixel offset (not Box2D meter offset)
		void ApplyForce(const umath::vector2& force, const umath::vector2& point);

		// Applies impulse to the center of the object
		// Force is usually considered to be in Newton seconds(Ns)
		void ApplyImpulse(const umath::vector2& impulse);
		// Applies impulse to a point on the object (offset from the center of the object)
		void ApplyImpulse(const umath::vector2& impulse, const umath::vector2& point);

		// Applies torque to the object
		// Force is usually considered to be in Newton metres(Nm)
		// Positive torque means counter-clockwise rotation
		void ApplyTorque(const float torque);

		// Sets the raw velocity of the object
		// Velocity in pixels per second
		void SetVelocity(const umath::vector2& velocity);
		const umath::vector2 GetVelocity() const;

		// Sets the size of the object(hitbox) in pixels
		void SetSize(const umath::vector2& size);
		// Sets the size of the object(hitbox) in Box2D units(meters)
		void SetUnitSize(const umath::vector2& size);
		// Same as above
		void SetSize(const float radius);
		void SetUnitSize(const float radius);

		// Returns the size of the object(hitbox) in pixels
		// Returns as a box size so diameter of a ball can be found in vector.x
		const umath::vector2 GetSize();
		// Returns the size of the object(hitbox) in Box2D units(meters)
		const umath::vector2 GetUnitSize();
		
		// Sets the position of the object in pixels
		void SetPosition(const umath::vector2& position);
		// Get the position in pixels
		const umath::vector2 GetPosition();
		// Set the angle of the object in degrees
		void SetAngle(const float angle);
		// Get the angle of the object in degrees
		const float GetAngle();

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

	private:
		void defaults();
		void init();

		Rigidbody();

		b2World* m_world;
		b2Body* m_body;
		// For resizing etc...
		b2FixtureDef m_fixtureDef;
		COLLIDER_TYPE m_collider;
		umath::vector2 m_size;
	};
}

#endif