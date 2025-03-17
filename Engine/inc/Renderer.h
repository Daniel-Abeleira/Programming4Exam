#pragma once
#include <SDL.h>
#include "Singleton.h"

namespace engine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* renderer{};
		SDL_Window* window{};
		SDL_Color clear_color{};
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return clear_color; }
		void SetBackgroundColor(const SDL_Color& color) { clear_color = color; }
	};


}