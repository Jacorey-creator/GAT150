#pragma once
#include "Framework/Actor.h"
#include "Framework/Framework.h"

namespace afro
{
	class Enemy : public afro::Actor
	{
	public:

		CLASS_DECLARATION(Enemy)

			/*Enemy(float speed, float turnRate, const afro::Transform& transform) :
			Actor{ transform },
			m_speed{ speed },
			m_turnRate{ turnRate }
		{
			m_fireRate = 1.0f;
			m_fireTimer = m_fireRate;
		}*/
			bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

		friend class SpaceGame;


	private:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;

		afro::PhysicsComponent* m_physicsComponent = nullptr;
	};
}