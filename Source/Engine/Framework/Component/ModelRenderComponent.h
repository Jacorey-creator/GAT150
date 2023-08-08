#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace afro {
	class ModelRenderComponent : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(Renderer& renderer);

	};

}
