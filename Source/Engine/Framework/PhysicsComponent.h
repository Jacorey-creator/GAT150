#pragma once
#include "Framework/Components.h"
#include "box2d/include/box2d/box2d.h"
#include "Core/Vector2.h"
namespace afro
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const vec2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;
		virtual void SetPosition(const vec2& position) {}

		virtual void SetVelocity(const vec2& velocity) { this->velocity = velocity; }
		virtual void SetGravityScale(float scale) {}
	public:
		vec2 velocity;
		vec2 m_acceleration;
		float m_mass = 1.0f;
		float m_damping = 0;
	};
}