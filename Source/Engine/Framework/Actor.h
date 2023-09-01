#pragma once
#include <rapidjson/include/rapidjson/document.h>
#include "Framework/Object.h"
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components.h"
#include <memory>

namespace afro
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;
		Actor(const afro::Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(afro::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component>component);
		template<typename T>
		T* GetComponent();

		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}

		class Scene* m_scene = nullptr;
		friend class Scene;
		friend class Components;

		class Game* m_game = nullptr;

		afro::Transform transform;
		std::string tag;

		float lifespan = -1.0f;
		bool destroyed = false;
		bool persistant = false;
		bool prototype = false;
	protected:
		std::vector<std::unique_ptr<Component>> components;

	};


	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}

}