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

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player) 
	{
		afro::Vector2 direction = player->m_transform.position - m_transform.position;
		
		float turnAngle = afro::vec2::SignedAngle(forward, direction.Normalized());

		m_transform.rotation += turnAngle * dt;
		
		m_transform.rotation = direction.Angle() + afro::HalfPi;
		if (std::fabs(turnAngle) < afro::DegreesToRadians(30.0f))
		{

		}
	}

	m_transform.position += forward * m_speed * afro::g_time.GetDeltaTime();
	m_transform.position.x = afro::Wrap(m_transform.position.x, (float)afro::g_renderer.GetWidth());
	m_transform.position.y = afro::Wrap(m_transform.position.y, (float)afro::g_renderer.GetHeight());

	//create weapon
	m_fireTimer -= dt;
	if (m_fireTimer <= 0)
	{
		//create weapon

		afro::Transform transform{m_transform.position, m_transform.rotation, 0.5f };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, m_transform);
		weapon->m_tag = "EnemyBullet";
		std::unique_ptr<afro::SpriteComponent> component = std::make_unique<afro::SpriteComponent>();
		component->m_texture = GET_RESOURCE(afro::Texture,"bullet.png", afro::g_renderer);
		m_scene->Add(std::move(weapon));
		m_fireTimer = m_fireRate;
	}
}

bool Enemy::Initialize()
{
	Actor::Initialize();

	auto collisionComponent = GetComponent<afro::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<afro::RenderComponent>();
		if (renderComponent)
		{
		float scale = m_transform.scale;
		collisionComponent->m_radius = GetComponent<afro::RenderComponent>()->GetRadius();
		}
	}
	return true;
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "PlayerBullet") {
		m_game->AddPoints(1);
		m_destroyed = true;

		m_game->SetEntities(m_game->GetEntities() - 1);
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
		afro::Transform transform{ m_transform.position,0,1 };
		auto emitter = std::make_unique<afro::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
}
