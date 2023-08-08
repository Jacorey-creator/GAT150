#pragma once
#include "Core/Vector2.h"
#include "Framework/Resource.h"
#include <cstdarg>

struct SDL_Texture;

namespace afro
{
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(std::string filename, class Renderer& renderer);
		vec2 GetSize();
		
		friend class Renderer;
		
		virtual bool Create(std::string filename, ...) override;
	private:
		SDL_Texture* m_texture = nullptr;

	};
}
