#include "ParticleSystem.h"

namespace afro {
	ParticleSystem g_particleSystem(1000);
	void afro::ParticleSystem::Update(float dt)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Update(dt);
		}
	}

	void afro::ParticleSystem::Draw(Renderer& renderer)
	{
		for (auto& particle : m_particles)
		{
			if (particle.m_isActive) particle.Draw(renderer);
		}
	}

	Particle* afro::ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : m_particles)
		{
			if (!particle.m_isActive) return &particle;
		}

		return nullptr;
	}
}