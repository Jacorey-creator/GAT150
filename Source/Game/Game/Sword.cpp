#include "Sword.h"


namespace afro
{

	bool Weapon::Initialize()
	{

		Actor::Initialize();


		//m_physicsComponent = GetComponent<afro::PhysicsComponent>();
		auto collisionComponent = GetComponent<afro::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<afro::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<afro::RenderComponent>()->GetRadius();
			}
		}
		return true;
	}

	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed)
	}

	void Weapon::Update(float dt)
	{
		Actor::Initialize();

		afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(transform.rotation);
		transform.position += forward * speed * afro::g_time.GetDeltaTime();

		transform.position.x = afro::Wrap(transform.position.x, (float)afro::g_renderer.GetWidth());
		transform.position.y = afro::Wrap(transform.position.y, (float)afro::g_renderer.GetHeight());
	}

	void Weapon::OnCollision(Actor* other)
	{
		if (other->tag != tag) {
			destroyed = true;
		}
	}
}