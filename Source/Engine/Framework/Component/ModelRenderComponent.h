#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace afro {
	class ModelRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelRenderComponent)

		bool Initialize() override;
		void Update(float dt);
		void Draw(Renderer& renderer);
		virtual float GetRadius() { return m_model->GetRadius(); }
	public:
	std::string modelName;
	res_t<Model> m_model;
	};


}
