#pragma once
#include "CoilyState.h"
#include <memory>
#include "IsometricGrid.h"
namespace qbert
{
	class EggFallingState final : public CoilyState
	{
	public:
		EggFallingState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid) : CoilyState(std::move(pCoilyObject), std::move(pPiramid)) {}

		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override { return nullptr; };
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;

	private:
		float m_speed{ 0.f };
		static inline const SDL_Rect m_spriteSrcRect = SDL_Rect{ 80, 16, 16, 16 };
		std::unique_ptr<IsometricGridPosition> m_pGoalPosition;
	};
}

