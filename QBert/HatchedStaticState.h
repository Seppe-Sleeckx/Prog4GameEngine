#pragma once
#include "CoilyState.h"
#include <memory>
#include <SDL_rect.h>
#include "StateHelpers.h"
#include <chrono>
namespace qbert
{
	class HatchedStaticState final : public CoilyState
	{
	public:
		HatchedStaticState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid, FacingDirection facingDirection) : CoilyState(std::move(pCoilyObject), std::move(pPiramid)) 
		{
			switch (facingDirection)
			{
			case FacingDirection::Left_Up:
				m_spriteSrcRect = std::make_unique<SDL_Rect>(32, 48, 16, 16);
				break;
			case FacingDirection::Left_Down:
				m_spriteSrcRect = std::make_unique<SDL_Rect>(96, 48, 16, 16);
				break;
			case FacingDirection::Right_Up:
				m_spriteSrcRect = std::make_unique<SDL_Rect>(0, 48, 16, 16 );
				break;
			case FacingDirection::Right_Down:
				m_spriteSrcRect = std::make_unique<SDL_Rect>(64, 48, 16, 16 );
				break;
			}
		};

		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override { return nullptr; };
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;

	private:
		const std::chrono::seconds m_jumpCooldown{ 1 }; //falls for x amount of seconds before calling reset
		std::chrono::duration<float> m_elapsedTime{};
		std::unique_ptr<SDL_Rect> m_spriteSrcRect;
	};

}

