#pragma once
#include "Framework/Actor.h"

class Player : public afro::Actor
{
public:
	Player(float speed, float turnRate, const afro::Transform& transform, std::shared_ptr<afro::Model> model) :
		Actor{ transform,model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 100;
};