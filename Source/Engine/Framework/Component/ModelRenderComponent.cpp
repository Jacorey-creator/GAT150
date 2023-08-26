#include "ModelRenderComponent.h"
#include "Framework/ResourceManager.h"
#include "Framework/Actor.h"

namespace afro
{
	CLASS_DEFINITION(ModelRenderComponent)

		bool ModelRenderComponent::Initialize()
	{
		if (!modelName.empty())m_model = GET_RESOURCE(Model, modelName);
		return true;
	}

	void afro::ModelRenderComponent::Update(float dt)
	{
	}

	void afro::ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
	}

	void ModelRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);

	}

}