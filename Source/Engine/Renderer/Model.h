#pragma once
#include "Core/Core.h"
#include "Renderer.h"
#include <vector>

namespace afro
{
	class Model : public Resource {
	public:
		Model() = default;
		//Model(const std::vector<vec2>& points) : m_points{ points } {}


		virtual bool Create(std::string filename, ...)/*override*/;
		bool Load(const std::string& filname);
		void Draw(class Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);
		float GetRadius();
	

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius;

	};
}