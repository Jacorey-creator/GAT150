#include "TextRenderComponent.h"
#include "ResourceManager.h"
#include "Actor.h"

namespace afro
{
	CLASS_DEFINITION(TextRenderComponent)

	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other)
	{
		text = other.text;
		//<set font name from other font name>
		fontName = other.fontName;
			//<set font size from other font size>
		fontSize = other.fontSize;
		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());
	}

	bool TextRenderComponent::Initialize()
	{
		if (!fontName.empty()) m_text = std::make_unique<afro::Text>(GET_RESOURCE(afro::Font, fontName, fontSize));
				
		return true;
	}
	void TextRenderComponent::Update(float dt)
	{
	}
	void TextRenderComponent::Draw(Renderer& renderer)
	{
		// update the text if changed
		if (m_changed)
		{
			m_changed = false;
			// create text using text string and color
			m_text->Create(renderer, text, color);
		}
		// draw text
		m_text->Draw(renderer, m_owner->transform);
	}
	void TextRenderComponent::SetText(const std::string& string)
	{
		// check if text has changed, if changed set new string and update
		if (string != text)
		{
			text = string;
			m_changed = true;
		}
	}
	void TextRenderComponent::Read(const json_t& value)
	{
		/*<read data text>*/
		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
		READ_DATA(value, color);
	}
}

