#pragma once
#include <memory>

#include "Component.h"
#include "Texture2D.h"
#include <SDL_rect.h>

namespace dae
{
	class GameObject;
	class Texture2DRenderer final : public Component
	{
	public:
		Texture2DRenderer(std::shared_ptr<GameObject> gameObject);
		virtual ~Texture2DRenderer() override;
		Texture2DRenderer(const Texture2DRenderer& other) = delete;
		Texture2DRenderer(Texture2DRenderer&& other) = delete;
		Texture2DRenderer& operator=(const Texture2DRenderer& other) = delete;
		Texture2DRenderer& operator=(Texture2DRenderer&& other) = delete;

		virtual void Update() override {};
		virtual void FixedUpdate() override{};
		virtual void Render() const override;
		void SetTexture(const std::string& filename);
		void SetSrcRect(const SDL_Rect& src_rect);
		const SDL_Rect& GetSrcRect() { return *m_srcRect.get(); }

	private:
		std::shared_ptr<Texture2D> m_texture;
		std::unique_ptr<SDL_Rect> m_srcRect;
	};
}