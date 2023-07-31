#include "Player.h"
#include "Input/Input.h"
#include "Game/Sword.h"
#include "Framework/Scene.h"
#include "SpaceGame.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ModelManager.h"

void Player::Update(float dt)
{
	Actor::Update(dt);
	//movement
	float rotate = 0;
	if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * afro::g_time.GetDeltaTime();

	float thrust = 0;
	if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * afro::g_time.GetDeltaTime();

	m_transform.position.x = afro::Wrap(m_transform.position.x, (float)afro::g_renderer.GetWidth());
	m_transform.position.y = afro::Wrap(m_transform.position.y, (float)afro::g_renderer.GetHeight());

	// fire weapon
	if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && 
		!afro::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		//create weapon
		
		afro::Transform transform{m_transform.position, m_transform.rotation, 1 };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f,m_transform, afro::g_manager.Get("Energy_Ball.txt"));
		
		weapon->m_tag = "PlayerBullet";
		m_scene->Add(std::move(weapon));
		afro::g_audioSystem.PlayOneShot("hit",false);
	}
}

void Player::OnCollision(Actor* other)
{
	Player* p = dynamic_cast<Player*>(other);
	if (other->m_tag == "EnemyBullet") {
		m_health - 1.0f;
		if (m_health <= 0) { m_destroyed = true; }

		m_game->SetLives(m_game->GetLives() - 1);
		if (m_game->GetLives() < 1)
		{
			m_destroyed = true;
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);
		}
	}
	
}

