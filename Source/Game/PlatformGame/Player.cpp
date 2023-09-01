#include "Player.h"
#include "PlatformGame/PlatGame.h"
#include "Input/Input.h"
#include "Framework/Scene.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ModelManager.h"
#include <Framework/Components/SpriteComponent.h>
#include <Framework/ResourceManager.h>
#include <Framework/PhysicsComponent.h>
#include <Framework/Components/CircleCollisionComponent.h>
#include "Framework/Event/EventManager.h"
#include "Framework/Components/SpriteAnimComponent.h"

namespace afro
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<afro::PhysicsComponent>();
		m_spriteComponent = GetComponent<SpriteAnimComponent>();
		
		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		bool OnGround = (groundcount > 0);
		vec2 velocity = m_physicsComponent->velocity;
		//movement
		float dir = 0;
		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		//transform.rotation += rotate * m_turnRate * afro::g_time.GetDeltaTime();


		afro::vec2 forward = afro::vec2{ 1,0 };

		if (dir)
		{
			velocity.x += m_speed * dir * ((OnGround) ? 1 : 0.25f);
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
			//m_physicsComponent->ApplyForce(forward * m_speed * dir * ((OnGround) ? 1 : 0.25f));
		}

		//transform.position.x = afro::Wrap(transform.position.x, (float)afro::g_renderer.GetWidth());
		//transform.position.y = afro::Wrap(transform.position.y, (float)afro::g_renderer.GetHeight());
		//jump
		if (OnGround && afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !afro::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) 
		{
			afro::vec2 up = afro::vec2{ 0, -1 } * dt;
			m_physicsComponent->SetVelocity( velocity + (up * jump));
		}
		if (velocity.y > 0) m_physicsComponent->SetGravityScale(5.0f);
		else m_physicsComponent->SetGravityScale(3.0f);

		//animation
		if (std::fabs(velocity.x) > 0.2f)
		{
			m_spriteComponent->flipH = (dir<-0.1f);
			m_spriteComponent->SetSequence("run");
		}
		else
		{
			m_spriteComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		Player* p = dynamic_cast<Player*>(other);
		if (other->tag == "Enemy") {
			m_health -= 1.0f;
			if (m_health <= 0)
			{
				destroyed = true;
				afro::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
			}
			


		}
		if (other->tag == "Ground") groundcount++;

	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundcount--;
	}


	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
		READ_DATA(value, m_health);

	}
}