#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace afro
{
	CLASS_DEFINITION(ModelRenderComponent)

	void afro::ModelRenderComponent::Update(float dt)
	{
	}

	void afro::ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_transform);
	}
}