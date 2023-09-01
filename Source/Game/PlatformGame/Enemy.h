#pragma once
#include "Framework/Actor.h"
#include "Framework/Factory.h"
#include "Framework/Components/EnginePhysicsComponent.h"

namespace afro
{
	class Enemy : public afro::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)


		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;


	public:
		float m_speed = 0;
		int groundcount = 0;
		float m_health = 100;

		class afro::PhysicsComponent* m_physicsComponent = nullptr;
	};
}