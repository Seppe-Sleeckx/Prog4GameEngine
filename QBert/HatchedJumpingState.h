#pragma once
#include "CoilyState.h"
#include "StateHelpers.h"
namespace qbert
{
	class HatchedJumpingState final : public CoilyState
	{
	public:
		HatchedJumpingState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid);
		virtual ~HatchedJumpingState() = default;

		virtual void OnEnter() override;
		virtual std::unique_ptr<CoilyState> Update() override { return nullptr; };
		virtual std::unique_ptr<CoilyState> FixedUpdate() override;

	private:
		FacingDirection m_facingDirection{ FacingDirection::Left_Down };
		glm::vec2 m_goalPos{ 0.f,0.f };
		const float m_speed{ 2.f };
	};
}
