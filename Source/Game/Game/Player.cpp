#include "Player.h"
#include "Input/Input.h"
#include "Game/Sword.h"
#include "Framework/Scene.h"
#include "SpaceGame.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ModelManager.h"
#include <Framework/Components/SpriteComponent.h>
#include <Framework/ResourceManager.h>
#include <Framework/PhysicsComponent.h>
#include <Framework/Components/CircleCollisionComponent.h>


namespace afro
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<afro::PhysicsComponent>();
		auto collisionComponent = GetComponent<afro::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<afro::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<afro::RenderComponent>()->GetRadius();
			}
		}
		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		//movement
		float rotate = 0;
		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_D))
		{
			rotate = 1;
		}
		//transform.rotation += rotate * m_turnRate * afro::g_time.GetDeltaTime();
		m_physicsComponent->ApplyTorque(rotate + m_turnRate);



		float thrust = 0;
		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(transform.rotation);
		transform.position += forward * m_speed * thrust * afro::g_time.GetDeltaTime();


		auto physicComponent = GetComponent<afro::PhysicsComponent>();
		m_physicsComponent->ApplyForce(forward * m_speed * thrust);


		transform.position.x = afro::Wrap(transform.position.x, (float)afro::g_renderer.GetWidth());
		transform.position.y = afro::Wrap(transform.position.y, (float)afro::g_renderer.GetHeight());

		// fire weapon
		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!afro::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			auto weapon = INSTANTIATE(Weapon, "Rocket")
			weapon->transform = { transform.position + forward * 30, transform.rotation, 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
			//create weapon
		}

	}


	void Player::OnCollisionEnter(Actor* other)
	{
		Player* p = dynamic_cast<Player*>(other);
		if (other->tag == "EnemyBullet") {
			m_health -= 1.0f;
			if (m_health <= 0)
			{
				destroyed = true;
				afro::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
			}


		}

	}


	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, m_turnRate);
		READ_DATA(value, m_health);

	}
}