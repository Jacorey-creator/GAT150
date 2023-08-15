#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace afro {

void afro::SpriteComponent::Update(float dt)
{
}

void SpriteComponent::Draw(Renderer& renderer)
{
	renderer.DrawTexture(m_texture.get(), m_owner->m_transform);
	
	//std::cout << m_owner->m_transform.position.x << " " << m_owner->m_transform.position.y << std::endl;
}

}
