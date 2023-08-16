#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace afro 
{
	CLASS_DEFINITION(CircleCollisionComponent)

	void afro::CircleCollisionComponent::Update(float dt)
	{
	}

	bool CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
	{
		float distance = m_owner->m_transform.position.Distance(collision->m_owner->m_transform.position);
		float radius = m_radius + collision->m_radius;


		return (distance <= radius);
	}
}

