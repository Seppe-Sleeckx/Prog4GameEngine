#pragma once
#include "CoilyState.h"
#include <memory>
#include <SDL_rect.h>
namespace qbert
{
	class EggJumpingState final : public CoilyState
	{
	public:
		EggJumpingState(std::weak_ptr<dae::GameObject> pCoilyObject) : CoilyState(std::move(pCoilyObject)) {};
		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override { return nullptr; };
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;
	private:
		static inline const SDL_Rect m_spriteSrcRect = SDL_Rect{ 160, 32, 32, 32 };
		glm::vec2 m_goalISOPos{ 0.f,0.f };
	};
}

