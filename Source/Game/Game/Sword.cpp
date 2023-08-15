#include "Sword.h"

void Weapon::Update(float dt)
{
	Actor::Update(dt);

	afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * afro::g_time.GetDeltaTime();

	m_transform.position.x = afro::Wrap(m_transform.position.x, (float)afro::g_renderer.GetWidth());
	m_transform.position.y = afro::Wrap(m_transform.position.y, (float)afro::g_renderer.GetHeight());
}

bool Weapon::Initialize()
{
	Actor::Initialize();

	m_physicsComponent = GetComponent<afro::PhysicsComponent>();
	auto collisionComponent = GetComponent<afro::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<afro::RenderComponent>();
		if (renderComponent)
		{
		float scale = m_transform.scale;
		collisionComponent->m_radius = GetComponent<afro::RenderComponent>()->GetRadius();
		}
	}
	return true;
}

void Weapon::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag) {
		m_destroyed = true;
	}
}
