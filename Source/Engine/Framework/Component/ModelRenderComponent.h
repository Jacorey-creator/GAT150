#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace afro {
	class ModelRenderComponent : public RenderComponent
	{
	public:
		void Update(float dt);
		void Draw(Renderer& renderer);
		virtual float GetRadiu() { return m_model->GetRadius(); }
	res_t<Model> m_model;
	};


}
