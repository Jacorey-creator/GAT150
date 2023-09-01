
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
#include <Game/Player.h>

namespace afro
{

	bool PlatGame::Initialize()
	{
		afro::g_audioSystem.AddAudio("hit", "audio/hit.wav");
		afro::g_audioSystem.AddAudio("music", "audio/Background_Music.ogg");

		m_scene = std::make_unique<Scene>();
		m_scene->Load("Scenes/PlatformGame.json");
		m_scene->Load("Scenes/tilemap.json");
		m_scene->Initialize();


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
		{

			afro::g_audioSystem.PlayOneShot("music", true);
			auto actor = INSTANTIATE(Actor, "Crate");
			actor->Initialize();
			m_scene->Add(std::move(actor));
			
			if (g_inputSystem.GetKeyDown(SDL_SCANCODE_S))
			{
				auto actor = INSTANTIATE(Actor, "Coin");
				actor->Initialize();
				m_scene->Add(std::move(actor));


			}

		}
			break;
		case eState::StartGame:
			m_score = 0;
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