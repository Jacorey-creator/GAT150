
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"
#include "Renderer/Emitter.h"

#include "Audio/AudioSystem.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"
using namespace afro;


bool SpaceGame::Initialize()
{
	//create font
	m_font = std::make_unique<afro::Font>("Wedgie Regular.ttf", 30);
	m_titletext = std::make_unique<afro::Text>(m_font);
	m_titletext->Create(afro::g_renderer, "Galaxy Intruders", afro::Color{ 1, 1, 1, 1 });

	m_scoretext = std::make_unique<afro::Text>(m_font);
	m_scoretext->Create(afro::g_renderer, "Score", afro::Color{ 1, 1, 1, 1 });

	m_gameovertext = std::make_unique<afro::Text>(m_font);
	m_gameovertext->Create(afro::g_renderer, "GameOver", afro::Color{ 1, 1, 1, 1 });


	//load audio
	afro::g_audioSystem.AddAudio("hit", "hit.wav");
	afro::g_audioSystem.AddAudio("space", "space_song.wav");
	
	//make scene
	m_scene = std::make_unique<afro::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	if (afro::g_inputSystem.GetMouseButtonDown(0))
	{
		EmitterData data;
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
		Transform transform{ { g_inputSystem.GetMousePosition() }, 0, 1 };
		auto emitter = std::make_unique<Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	switch (m_state)
	{
	case eState::Title:
		afro::g_audioSystem.PlayOneShot("space", true);
		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) { m_state = eState::StartLevel; }
		break;
	case eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case eState::Game:
		m_spawntimer += dt;
		if (m_spawntimer >= m_spawntime)
		{
				if (m_lives <= 0) { m_state = eState::PlayerDeadStart; }
				
				if (m_entities >= 1) { break; }
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(afro::randomf(75.0f, 150.0f), afro::Pi, afro::Transform{ {afro::randomf(100.0f, 300.0f), afro::randomf(500.0f, 250.0f)},
				afro::randomf(afro::TwoPi), 3}, afro::g_manager.Get("cooler_ship.txt"));
				enemy->m_tag = "Enemy";
				enemy->m_game = this;
				m_scene->Add(std::move(enemy));
				m_entities++;
				
				if (m_score >= 100 ) {
					std::unique_ptr<Enemy> enemy_2 = std::make_unique<Enemy>(afro::randomf(60.0f, 450.0f), afro::Pi, afro::Transform{ {afro::randomf(100.0f, 300.0f),
						afro::randomf(50.0f, 70.0f)}, afro::randomf(afro::TwoPi), 7}, afro::g_manager.Get("Big_Ship.txt"));
					enemy_2->m_tag = "Enemy";
					enemy_2->m_game = this;
					m_scene->Add(std::move(enemy_2));
				}
		}

		break;
	case eState::StartLevel:
		m_scene->RemoveAll();
		m_entities = 0;
		afro::Game::SetLives(1);
		{
			std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, afro::Pi, afro::Transform{ {400, 300}, 0, 6 }, afro::g_manager.Get("ship.txt"));
			player->m_tag = "Player";
			player->m_game = this;

			m_scene->Add(std::move(player));
		}
		m_state = eState::Game;
		break;
	case eState::PlayerDeadStart:
		m_statetimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		m_state = eState::PlayerDead;
		break;
	case eState::PlayerDead:
    		m_statetimer -= dt;
		deathcount++;
		if (m_statetimer <= 0) 
		{
			m_state = eState::GameOver;
			m_statetimer = 3;
		}
		break;
	case eState::GameOver:
		m_statetimer -= dt;
		if(m_statetimer < 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	default:
		break;
	}
	m_highscoretext = std::make_unique<afro::Text>(m_font);
	m_highscoretext->Create(afro::g_renderer, std::to_string(m_score), {1,1,1,1});

	m_deathtext = std::make_unique<afro::Text>(m_font);
	m_deathtext->Create(afro::g_renderer, "You Perished " + std::to_string(deathcount), afro::Color{ 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(afro::Renderer& renderer)
{
	if (m_state == eState::Title) 
	{
		m_titletext->Draw(renderer, 400, 300);
	}
	
	if (m_state == eState::GameOver) 
	{
		m_gameovertext->Draw(renderer, 400, 300);
	}
	
	if (deathcount >= 1) 
	{
		m_deathtext->Draw(renderer, 420, 40);
	}
	m_scoretext->Draw(renderer, 40, 40);
	m_highscoretext->Draw(renderer, 300, 40);

	m_scene->Draw(renderer);

}
