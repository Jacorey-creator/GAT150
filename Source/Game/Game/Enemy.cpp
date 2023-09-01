#include "Enemy.h"
#include "Player.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Sword.h"
#include "Game/SpaceGame.h"
#include "Renderer/ModelManager.h"
#include <Renderer/Emitter.h>
#include <Framework/Components/SpriteComponent.h>
#include <Framework/ResourceManager.h>

namespace afro
{
	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			afro::Vector2 direction = player->transform.position - transform.position;

			float turnAngle = afro::vec2::SignedAngle(forward, direction.Normalized());

			transform.rotation += turnAngle * dt;
			m_physicsComponent->ApplyTorque(turnAngle);
			transform.rotation = direction.Angle() + afro::HalfPi;
			if (std::fabs(turnAngle) < afro::DegreesToRadians(30.0f))
			{

			}
		}
		m_physicsComponent->ApplyForce(forward + m_speed);
		transform.position += forward * m_speed * afro::g_time.GetDeltaTime();
		transform.position.x = afro::Wrap(transform.position.x, (float)afro::g_renderer.GetWidth());
		transform.position.y = afro::Wrap(transform.position.y, (float)afro::g_renderer.GetHeight());

		//create weapon
		m_fireTimer -= dt;
		if (m_fireTimer <= 0)
		{
			//create weapon

			//afro::Transform transform{transform.position, transform.rotation, 0.5f };
			//std::unique_ptr<WeaponComponent> weapon = std::make_unique<WeaponComponent>(400.0f, transform);
			//weapon->tag = "EnemyBullet";

			std::unique_ptr<afro::SpriteComponent> component = std::make_unique<afro::SpriteComponent>();
			component->m_texture = GET_RESOURCE(afro::Texture, "SpaceGame/Textures/bullet.png", afro::g_renderer);
			//m_scene->Add(std::move(weapon));
			m_fireTimer = m_fireRate;
		}
	}

	CLASS_DEFINITION(Enemy)


		bool Enemy::Initialize()
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


	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "PlayerBullet")
		{
			afro::EventManager::Instance().DispatchEvent("AddPoints", 100);
			//m_game->AddPoints(1);
			destroyed = true;
			m_game->SetEntities(m_game->GetEntities() - 1);

			//create explosion
			afro::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = afro::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = afro::Color{ 1, 0, 0, 1 };
			afro::Transform transform{ this->transform.position, 0, 1 };
			auto emitter = std::make_unique<afro::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
	}
	void Enemy::Read(const json_t& value)
	{
			Actor::Read(value);
		
			READ_DATA(value, m_speed);
			READ_DATA(value, m_turnRate);
			READ_DATA(value, m_fireRate);
			READ_DATA(value, m_fireTimer);
	}
}