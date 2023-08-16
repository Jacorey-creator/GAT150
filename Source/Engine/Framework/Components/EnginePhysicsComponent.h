#pragma once
#include "Framework/PhysicsComponent.h"
namespace afro
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)

		void Update(float dt);
		void ApplyForce(const vec2& force);
	public:
	};
}