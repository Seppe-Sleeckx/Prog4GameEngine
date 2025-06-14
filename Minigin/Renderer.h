#pragma once
#include <SDL.h>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const float x, const float y) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const SDL_Rect& src_rect, const float xScale = 1.f, const float yScale = 1.f) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& dest_rect, const SDL_Rect& src_rect) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }
	};
}

