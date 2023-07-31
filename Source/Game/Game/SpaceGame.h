#pragma once
#include "Framework/Game.h"
#include <Renderer/Font.h>
#include <Renderer/Text.h>

class SpaceGame : public afro::Game
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
	friend class Enemy;
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