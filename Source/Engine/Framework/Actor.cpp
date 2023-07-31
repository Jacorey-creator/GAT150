#include "Actor.h"
namespace afro {
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
		}
	}
	void Actor::Draw(afro::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
