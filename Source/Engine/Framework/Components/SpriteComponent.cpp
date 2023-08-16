#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace afro {
CLASS_DEFINITION(SpriteComponent)

void afro::SpriteComponent::Update(float dt)
{
}

void SpriteComponent::Draw(Renderer& renderer)
{
	renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	
}

}
