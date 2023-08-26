#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Input/Input.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Texture.h"
#include "Framework/ResourceManager.h"
#include <iostream>
#include <vector>
#include <thread>
#include <Renderer/Emitter.h>
#include  <cassert>
#include <array>
#include <functional>
#include "Physics/PhysicsSystem.h"


using namespace afro;





int main(int argc, char* argv[])
{

	afro::PhysicsSystem::Instance().Initialize();

	INFO_LOG("Initialize Engine");

	afro::MemoryTracker::Initialize();
	afro::seed_random((unsigned int)time(nullptr));
	afro::setFilePath("Assets/PlatformGame");


	afro::g_renderer.Initialize();
	afro::g_renderer.CreateWindow("CSC196", 800, 600);

	afro::g_inputSystem.Initialize();
	afro::g_audioSystem.Initialize();

	//std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	//game->Initialize();




	


	float speed = 200;
	constexpr float turnRate = afro::DegreesToRadians(180);

	// create texture
	res_t<afro::Texture> texture = GET_RESOURCE(afro::Texture, "SpaceGame/Textures/guy.png", afro::g_renderer);
	texture->Load("SpaceGame/Textures/Guy.png", g_renderer);

	//main game loop
	bool quit = false;
	while (!quit)
	{

		// update engine
		afro::g_time.Tick();
		afro::g_inputSystem.Update();
		afro::AudioSystem().Update();

		if (afro::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// update game
		//game->Update(afro::g_time.GetDeltaTime());
		afro::PhysicsSystem::Instance().Update(afro::g_time.GetDeltaTime());
		afro::g_particleSystem.Update(afro::g_time.GetDeltaTime());


		// draw
		afro::g_renderer.SetColor(0, 0, 0, 0);
		afro::g_renderer.BeginFrame();
		//game->Draw(afro::g_renderer);

		afro::g_renderer.DrawTexture(texture.get(), 0, 0, 0.0f);

		afro::g_particleSystem.Draw(g_renderer);

		afro::g_renderer.EndFrame();
	}

	return 0;
}