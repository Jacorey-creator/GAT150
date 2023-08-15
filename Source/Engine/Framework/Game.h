#pragma once
#include <memory>
#include "Game/Player.h"

namespace afro
{
	class Renderer;

	class Game {
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }

		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }

		int GetEntities() const { return m_entities; }
		void SetEntities(int ent) { m_entities = ent; }

	protected:
		std::unique_ptr<class Scene> m_scene;

		int m_score = 0;
		int m_lives = 1;
		int m_entities = 0;

	};
}