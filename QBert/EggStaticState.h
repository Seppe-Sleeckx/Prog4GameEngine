#pragma once
#include "CoilyState.h"
#include <SDL_rect.h>

namespace dae
{
	class EggStaticState final : public CoilyState
	{
	public:
		EggStaticState(std::weak_ptr<dae::GameObject> pCoilyObject) : CoilyState(std::move(pCoilyObject)) {};
		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override;
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;
		virtual void Render() override;
	private:
		float m_jumpTimer{ 0.f };
		static inline const SDL_Rect m_spriteSrcRect = SDL_Rect{ 128, 32, 32, 32 };

		bool HasReachedBottomOfPiramid();
	};
}

