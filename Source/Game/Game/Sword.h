#pragma once
#include "Framework/Actor.h"
#include "Core/Json.h"
#include "Framework/Framework.h"
#include "Player.h"

namespace afro
{

	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon)
	
		void Update(float dt) override;
		void OnCollision(Actor* other);
		bool Initialize() override;

	private:
		float speed = 0;
		float m_turnRate = 0;

		class afro::PhysicsComponent* m_physicsComponent = nullptr;

	};
}