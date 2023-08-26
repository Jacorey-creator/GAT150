#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Game/Enemy.h"
#include "Framework/Event/EventManager.h"

namespace afro
{

	class PlatGame : public afro::Game, afro::IEventListener
	{
	public:
		enum eState
		{
			Title,
			StartGame,
			StartLevel,
			Game,
			PlayerDeadStart,
			PlayerDead,
			GameOverStart,
			GameOver
		};
	public:
		virtual bool Initialize() override;
		virtual void Shutdown() override;

		virtual void Update(float dt) override;
		virtual void Draw(afro::Renderer& renderer) override;

		void SetState(eState state) { m_state = state; }

		void OnAddPoints(const afro::Event& event);
		void OnPlayerDead(const afro::Event& event);
		friend class afro::Enemy;
	private:
		eState m_state = eState::Title;
		float m_statetimer = 0;
		float m_spawntimer = 0;
		float m_spawntime = 3;
		int deathcount = 0;



		std::shared_ptr<afro::Font> m_font;
		std::unique_ptr<afro::Text> m_scoretext;
		std::unique_ptr<afro::Text> m_highscoretext;
		std::unique_ptr<afro::Text> m_titletext;
		std::unique_ptr<afro::Text> m_gameovertext;
		std::unique_ptr<afro::Text> m_deathtext;

	};
}