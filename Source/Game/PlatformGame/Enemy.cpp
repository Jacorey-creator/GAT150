#include "Enemy.h"
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
#include "Framework/Framework.h"
#include "Player.h"

namespace afro
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<afro::PhysicsComponent>();


		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);
		//movement

		//transform.rotation += rotate * m_turnRate * afro::g_time.GetDeltaTime();

		afro::vec2 forward = afro::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();

		if (player)
		{
			afro::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * m_speed);
		}

		m_physicsComponent->ApplyForce(forward * m_speed);


		transform.position.x = afro::Wrap(transform.position.x, (float)afro::g_renderer.GetWidth());
		transform.position.y = afro::Wrap(transform.position.y, (float)afro::g_renderer.GetHeight());
	

	}


	void Enemy::OnCollisionEnter(Actor* other)
	{
		
		if (other->tag == "Ground") { groundcount++;}
		

	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundcount--;

	}


	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, m_health);
	}
}