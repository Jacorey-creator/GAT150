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
	m_transform.rotation += rotate * m_turnRate * afro::g_time.GetDeltaTime();

	float thrust = 0;
	if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * afro::g_time.GetDeltaTime();

	//auto physicComponent = GetComponent<afro::PhysicsComponent>();
	m_physicsComponent->ApplyForce(forward * m_speed * thrust);


	m_transform.position.x = afro::Wrap(m_transform.position.x, (float)afro::g_renderer.GetWidth());
	m_transform.position.y = afro::Wrap(m_transform.position.y, (float)afro::g_renderer.GetHeight());

	// fire weapon
	if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && 
		!afro::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create weapon
		
		afro::Transform transform{m_transform.position, m_transform.rotation, 1 };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f,m_transform);
		
		weapon->m_tag = "PlayerBullet";
		auto component = std::make_unique<afro::SpriteComponent>();
 		component->m_texture = GET_RESOURCE(afro::Texture, "bullet.png", afro::g_renderer);
		weapon->AddComponent(std::move(component));

		auto collisionComponent = std::make_unique<afro::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));
		m_scene->Add(std::move(weapon));
		afro::g_audioSystem.PlayOneShot("hit",false);
	}

}

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
		float scale = m_transform.scale;
		collisionComponent->m_radius = GetComponent<afro::RenderComponent>()->GetRadius();
		}
	}
	return true;
}

void Player::OnCollision(Actor* other)
{
	Player* p = dynamic_cast<Player*>(other);
	if (other->m_tag == "EnemyBullet") {
		m_health -= 1.0f;
		if (m_health <= 0) { m_destroyed = true; }

		m_game->SetLives(m_game->GetLives() - 1);
		if (m_game->GetLives() < 1)
		{
			m_destroyed = true;
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);
		}
	}
	
}

