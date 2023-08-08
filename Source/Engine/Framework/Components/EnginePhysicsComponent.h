#pragma once
#include "Framework/PhysicsComponent.h"
namespace afro
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
		void Update(float dt);
		void ApplyForce(const vec2& force);
	public:
	};
}