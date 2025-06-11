#pragma once
#include "CoilyState.h"
#include <memory>
#include <SDL_rect.h>
#include "IsometricGridPositionComponent.h"
namespace qbert
{
	class EggJumpingState final : public CoilyState
	{
	public:
		EggJumpingState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid) : CoilyState(std::move(pCoilyObject), std::move(pPiramid)) {};
		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override { return nullptr; };
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;
	private:
		static inline const SDL_Rect m_spriteSrcRect = SDL_Rect{ 96, 16, 16, 16 };
		std::unique_ptr<IsometricGridPosition> m_pGoalPosition;
		const float m_speed{ 0.1f };
	};
}

