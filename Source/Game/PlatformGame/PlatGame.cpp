
#include "Renderer/Texture.h"
#include "Framework/Scene.h"
#include "Renderer/Emitter.h"
#include "Framework/Framework.h"
#include "PlatGame.h"

#include "Audio/AudioSystem.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"


#include "Framework/ResourceManager.h"
#include "Framework/Components/EnginePhysicsComponent.h"
#include <Framework/Components/CircleCollisionComponent.h>

#include "Framework/Event/EventManager.h"

namespace afro
{

	bool PlatGame::Initialize()
	{
		afro::setFilePath("PlatformGame");
		afro::g_audioSystem.AddAudio("hit", "audio/hit.wav");

		m_scene->Load("Platformer/Scenes/PlatformGame.json");
		m_scene->Initialize();

		//m_scene->SetGame(this);
		EVENT_SUBSCRIBE("OnAddPoints", PlatGame::OnAddPoints);
		EVENT_SUBSCRIBE("OnPlayerDead", PlatGame::OnPlayerDead);
		return true;
	}

	void PlatGame::Shutdown()
	{
	}

	void PlatGame::Update(float dt)
	{
	
		switch (m_state)
		{
		case eState::Title:
			break;
		case eState::StartGame:
			m_score = 0;
			m_lives = 3;
			m_state = eState::StartLevel;
			break;
		case eState::Game:
			
			break;
		case eState::StartLevel:
			m_scene->RemoveAll(true);
			m_state = eState::Game;
			break;
		case eState::PlayerDeadStart:
		
			break;
		case eState::PlayerDead:
		
			break;
		case eState::GameOver:
		
			break;
		default:
			break;
		}
		m_scene->Update(dt);
	}

	void PlatGame::Draw(afro::Renderer& renderer)
	{
		m_scene->Draw(renderer);
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


	}

	void PlatGame::OnAddPoints(const afro::Event& event)
	{
		m_score += std::get<int>(event.data);
	}

	void PlatGame::OnPlayerDead(const afro::Event& event)
	{
		m_lives--;
		m_state = eState::PlayerDeadStart;
	}
}