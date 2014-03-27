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
		Rigidbody(b2World* world, const COLLIDER_TYPE collider = COLLIDER_BOX,
			const std::string name = "Rigidbody");
		Rigidbody(b2World* world, const COLLIDER_TYPE collider, 
			const umath::vector2& size, const std::string name = "Rigidbody");
		~Rigidbody();

		void Update(float dt);
		bool isInitialized() const;

	private:
		void defaults();
		void init();

		bool m_isInitialized;

		Rigidbody();

		b2World* m_world;
		b2Body* m_body;
		COLLIDER_TYPE m_collider;
		umath::vector2 m_size;
	};
}

#endif