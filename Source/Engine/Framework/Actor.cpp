#include "Actor.h"
#include "Component/RenderComponent.h"
namespace afro {
	
	CLASS_DEFINITION(Actor)

	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f) 
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
			if (m_lifespan <= 0)
			{
				m_destroyed = true;
			}
			for (auto& component : afro::Actor::m_components)
			{
				component->Update(dt);
			}
		}
	}
	void Actor::Draw(afro::Renderer& renderer)
	{
		for (auto& component : m_components) 
		{
			RenderComponent* renderercomponent = dynamic_cast<RenderComponent*>(component.get());

			if (renderercomponent) { renderercomponent->Draw(renderer); }
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		
		m_components.push_back(std::move(component));
	}

	bool Actor::Initialize()
	{
		for (auto& component : m_components)
		{
			component->Initialize();
		}
		return true;
	}
	void Actor::OnDestroy()
	{
		for (auto& component : m_components)
		{
			component->OnDestroy();
		}
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		return true;
	}
}
