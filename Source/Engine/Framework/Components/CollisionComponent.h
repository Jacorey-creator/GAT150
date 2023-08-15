#pragma once
#include "Framework/Components.h"
namespace afro
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision) = 0;
	public:
		float m_radius = 0;
	};
}