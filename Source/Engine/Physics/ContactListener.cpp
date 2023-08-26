#include "ContactListener.h"
#include "Framework/Box2dCollisionComponent.h"
#include "Framework/Components/CollisionComponent.h"
#include <Framework/Actor.h>

namespace afro
{
	void afro::ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;
			actorA->OnCollisionEnter(actorB);
			actorB->OnCollisionEnter(actorA);
			auto collisionA = actorA->GetComponent<CollisionComponent>();
			if (collisionA)
			{
				//collisionA->OnCollisionEnter(actorB);
			}

			auto collisionB = actorB->GetComponent<CollisionComponent>();
			if (collisionB)
			{
				//collisionB->OnCollisionEnter(actorA);
			}
		}

	}

	void afro::ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;
			actorA->OnCollisionExit(actorB);
			actorB->OnCollisionExit(actorA);
		}
	}
}