#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* engine::Font::GetFont() const
{
	return TTF_font;
}

engine::Font::Font(const std::string& fullPath, unsigned int size) : TTF_font(nullptr)
{
	TTF_font = TTF_OpenFont(fullPath.c_str(), size);
	if (TTF_font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

engine::Font::~Font()
{
	TTF_CloseFont(TTF_font);
}
