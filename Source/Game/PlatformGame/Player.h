#pragma once
#include "Framework/Actor.h"
#include "Framework/Factory.h"
#include "Framework/Components/EnginePhysicsComponent.h"

namespace afro
{
	class Player : public afro::Actor
	{
	public:
		CLASS_DECLARATION(Player)


			bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;


	public:
		float m_speed = 0;
		float maxSpeed = 0;
		float jump = 0;
		int groundcount = 0;
		float m_health = 100;

		 afro::PhysicsComponent* m_physicsComponent = nullptr;
		 class SpriteAnimComponent* m_spriteComponent = nullptr;
	};
}