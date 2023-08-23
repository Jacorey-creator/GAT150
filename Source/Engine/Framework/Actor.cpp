#include "Actor.h"
#include "Framework/Object.h"
#include "Component/RenderComponent.h"
namespace afro {
	
	CLASS_DEFINITION(Actor)

	void Actor::Update(float dt)
	{
		if (lifespan != -1.0f) 
		{
			lifespan -= dt;
			destroyed = (lifespan <= 0);
			if (lifespan <= 0)
			{
				destroyed = true;
			}
			for (auto& component : afro::Actor::components)
			{
				component->Update(dt);
			}
		}
	}
	void Actor::Draw(afro::Renderer& renderer)
	{
		for (auto& component : components) 
		{
			RenderComponent* renderercomponent = dynamic_cast<RenderComponent*>(component.get());

			if (renderercomponent) { renderercomponent->Draw(renderer); }
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		
		components.push_back(std::move(component));
	}

	Actor::Actor(const Actor& other)
	{
		name = other.name;
		name = other.tag;
		name = other.lifespan;
		transform = other.transform;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components)
		{
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(cloneComponent));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}
		return true;
	}
	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}

	void Actor::Read(const rapidjson::Value& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, persistant);
		READ_DATA(value, prototype);
		READ_DATA(value, lifespan);

		if(HAS_DATA(value, transform))	transform.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type)
				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}
	}
}
