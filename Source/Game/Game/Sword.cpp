#include "Sword.h"


namespace afro
{
	CLASS_DEFINITION(Weapon)

	bool Weapon::Initialize()
	{

		Actor::Initialize();

		m_physicsComponent = GetComponent<afro::PhysicsComponent>();
		
		auto collisionComponent = GetComponent<afro::CollisionComponent>();
		if (collisionComponent)
		{
			
		}
		return true;
	}


	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, m_turnRate);
	}

	void Weapon::Update(float dt)
	{
		Actor::Initialize();

		afro::vec2 forward = afro::vec2{ 0,-1 }.Rotate(transform.rotation);
 		m_physicsComponent->SetVelocity(forward * speed);

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