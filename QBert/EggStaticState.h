#pragma once
#include "CoilyState.h"
#include <SDL_rect.h>

namespace qbert
{
	class EggStaticState final : public CoilyState
	{
	public:
		EggStaticState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid) : CoilyState(std::move(pCoilyObject), std::move(pPiramid)) {};
		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override;
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;
	private:
		float m_jumpTimer{ 0.f };
		static inline const SDL_Rect m_spriteSrcRect = SDL_Rect{ 80, 16, 16, 16 };

		bool HasReachedBottomOfPiramid();
	};
}