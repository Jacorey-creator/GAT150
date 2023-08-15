#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/EnginePhysicsComponent.h"

class Player : public afro::Actor
{
public:
	Player(float speed, float turnRate, const afro::Transform& transform) :
		Actor{ transform},
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 100;

	class afro::PhysicsComponent* m_physicsComponent = nullptr;
};