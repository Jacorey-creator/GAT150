

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Input/Input.h"
#include "Audio/AudioSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include "Renderer/ParticleSystem.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <thread>
#include <Renderer/Emitter.h>



using namespace afro;

class Star
{
public:
	Star(const afro::Vector2& pos, const afro::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}
	void Update(int width, int height)
	{
		m_pos += m_vel * afro::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}
public:
	afro::Vector2 m_pos;
	afro::Vector2 m_vel;
};


int main(int argc, char* argv[]) 
{
	afro::MemoryTracker::Initialize();
	afro::seed_random((unsigned int)time(nullptr));
	afro::setFilePath("Assets");
	//std::unique_ptr<int> up = std::make_unique<int>(10);
	//int m = afro::Max(4.0f, 3.0f);
	//int m2 = afro::Max(4, 3);

	afro::g_renderer.Initialize();
	afro::g_renderer.CreateWindow("CSC196", 800, 600);

	afro::g_inputSystem.Initialize();
	afro::g_audioSystem.Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();


	/*afro::vec2 v{5, 5};
	v.Normalize();*/

	std::vector<Star> stars;
	for (int i = 0; i < 100; i++)
	{
		afro::Vector2 pos(afro::random(afro::g_renderer.GetWidth()), afro::random(afro::g_renderer.GetHeight()));
		afro::Vector2 vel(afro::Vector2(afro::randomf(1, 4), 0.0f));
		stars.push_back(Star(pos, vel));
	}
	

	float speed = 200;
	constexpr float turnRate = afro::DegreesToRadians(180);

	//main game loop
	bool quit = false;
	while (!quit)
	{
		afro::g_inputSystem.GetMousePosition();
		if(afro::g_inputSystem.GetMouseButtonDown(SDL_BUTTON(0))) std::cout << "Left Mouse Button" << afro::g_inputSystem.GetMousePosition().x << "," << afro::g_inputSystem.GetMousePosition().y << std::endl;
		if(afro::g_inputSystem.GetMouseButtonDown(SDL_BUTTON(1))) std::cout << "Middle Mouse Button" << afro::g_inputSystem.GetMousePosition().x << "," << afro::g_inputSystem.GetMousePosition().y << std::endl;
		if(afro::g_inputSystem.GetMouseButtonDown(SDL_BUTTON(2))) std::cout << "Right Mouse Button" << afro::g_inputSystem.GetMousePosition().x << "," << afro::g_inputSystem.GetMousePosition().y << std::endl;
		
	
		


		// update engine
		afro::g_time.Tick();
		afro::g_inputSystem.Update();
		afro::AudioSystem().Update();

		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		
		// update game
		game->Update(afro::g_time.GetDeltaTime());
		afro::g_particleSystem.Update(afro::g_time.GetDeltaTime());


		// draw
		afro::g_renderer.SetColor(0, 0, 0, 0);
		afro::g_renderer.BeginFrame();
		for (auto& star : stars)
		{
			star.Update(afro::g_renderer.GetWidth(), afro::g_renderer.GetHeight());

			afro::g_renderer.SetColor(afro::random(256), afro::random(256), afro::random(256), 255);
			afro::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}
		game->Draw(afro::g_renderer);

		afro::g_particleSystem.Draw(g_renderer);

		afro::g_renderer.EndFrame();
	}
	stars.clear();

	return 0;
}