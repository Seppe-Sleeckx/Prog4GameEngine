#pragma once
#include "CoilyState.h"
#include <memory>
#include <SDL_rect.h>
namespace qbert
{
	class HatchedStaticState final : public CoilyState
	{
	public:
		HatchedStaticState(std::weak_ptr<dae::GameObject> pCoilyObject) : CoilyState(std::move(pCoilyObject)) {};

		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override { return nullptr; };
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;

	private:
		enum FacingDirection {
			Left_Up,
			Left_Down,
			Right_Up,
			Right_Down
		};

		float m_jumpTimer{ 0.f };
		FacingDirection m_facingDirection;
		SDL_Rect m_spriteSrcRect;
	};

}

