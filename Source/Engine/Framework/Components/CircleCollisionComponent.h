#pragma once
#include "Framework/Components.h"
#include "CollisionComponent.h"
namespace afro
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:

		CLASS_DECLARATION(CircleCollisionComponent)
		virtual void Update(float dt) override;

		bool CheckCollision(CollisionComponent* collision);
		float m_radius = 0;

	};
}