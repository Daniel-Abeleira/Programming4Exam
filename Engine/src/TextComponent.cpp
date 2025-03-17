#include <stdexcept>
#include <SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

engine::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> TTF_font)
	: Component(), needs_update(true), text(text), TTF_font(std::move(TTF_font)), text_texture(nullptr)
{}

void engine::TextComponent::Update(float delta_time)
{
	delta_time; //To get rid of the unreferenced warning treated as error
	if (needs_update)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(TTF_font->GetFont(), text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		text_texture = std::make_shared<Texture2D>(texture);
		needs_update = false;
	}
}

void engine::TextComponent::Render() const
{
	if (text_texture != nullptr)
	{
		const auto& pos = transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*text_texture.get(), pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void engine::TextComponent::SetText(const std::string& new_text)
{
	text = new_text;
	needs_update = true;
}

void engine::TextComponent::SetPosition(const float x, const float y)
{
	transform.SetPosition(x, y, 0.0f);
}
