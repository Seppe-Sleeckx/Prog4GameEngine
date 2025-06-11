#pragma once
#include "CoilyState.h"
namespace qbert
{
	class HatchedJumpingState final : public CoilyState
	{
	public:
		HatchedJumpingState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid) : CoilyState(std::move(pCoilyObject), std::move(pPiramid)) {};

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

		FacingDirection m_facingDirection; //TODO
		SDL_Rect m_spriteSrcRect; //TODO
		glm::vec2 m_goalPos{ 0.f,0.f };
	};
}
