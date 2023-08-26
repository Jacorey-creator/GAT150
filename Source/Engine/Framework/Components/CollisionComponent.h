#pragma once
#include "Framework/Components.h"
namespace afro
{
	class CollisionComponent : public Component
	{
	public:


		virtual bool CheckCollision(CollisionComponent* collision) { return true;  }
	public:
		float m_radius = 0;
	};
}