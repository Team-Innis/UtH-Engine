#pragma once
#ifndef RIGIDBODY_H_UTH
#define RIGIDBODY_H_UTH

#include <UtH/Engine/Component.hpp>
#include <Box2D/Box2D.h>

namespace uth
{
	const float PIXELS_PER_METER = 50.f;

	class Rigidbody : public Component
	{
	public:
		Rigidbody(b2World* world, const std::string name = "Rigidbody");
		~Rigidbody();

		void Update(float dt);

		bool isInitialized() const;

	private:
		void init();

		bool m_isInitialized;

		Rigidbody();

		b2World* m_world;
		b2Body* m_body;
	};
}

#endif