#pragma once
#include "Framework/Components.h"
#include "CollisionComponent.h"
namespace afro
{
	class CircleCollisionComponent : public Component
	{
	public:


		virtual void Update(float dt) override;

		bool CheckCollision(CollisionComponent* collision);
		float m_radius = 0;

	};
}