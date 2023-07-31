#pragma once
#include "Vector2.h"
namespace afro
{
	class Transform
	{
	public:
		vec2 position;
		float rotation;
		float scale;
	public:
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}
	};
}