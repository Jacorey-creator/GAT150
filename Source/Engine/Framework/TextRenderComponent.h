#pragma once
#include "Component/RenderComponent.h"
#include "Framework/Object.h"
#include <Renderer/Text.h>


namespace afro
{
	class TextRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(TextRenderComponent)

		TextRenderComponent() = default;
		TextRenderComponent(const TextRenderComponent& other);

		bool Initialize() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		void SetText(const std::string& string);
	public:
		std::string text;
		std::string fontName;
		int fontSize = 0;
		Color color;
	private:
		bool m_changed = true;
		std::unique_ptr<Text> m_text;
	};
}
