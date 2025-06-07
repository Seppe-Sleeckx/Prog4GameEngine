#pragma once
#include "CoilyState.h"
namespace dae
{
	class HatchedJumpingState final : public CoilyState
	{
	public:
		HatchedJumpingState(std::weak_ptr<dae::GameObject> pCoilyObject) : CoilyState(std::move(pCoilyObject)) {};

		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override { return nullptr; };
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;
		virtual void Render() override;

	private:
		enum FacingDirection {
			Left_Up,
			Left_Down,
			Right_Up,
			Right_Down
		};

		FacingDirection m_facingDirection;
		SDL_Rect m_spriteSrcRect;
		glm::vec2 m_goalPos{ 0.f,0.f };
	};
}
