#pragma once
#include "Framework/Components.h"

namespace afro
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}