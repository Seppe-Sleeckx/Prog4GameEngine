#pragma once
#include "QbertState.h"
#include "StateHelpers.h"
namespace qbert
{
	class QbertMovingState final : public QbertState
	{
	public:
		QbertMovingState(std::weak_ptr<dae::GameObject> pQbertObject, std::weak_ptr<Piramid> pPiramid, FacingDirection move_direction) : QbertState(std::move(m_pQbertObject), std::move(pPiramid)), m_facingDirection{move_direction} {}
		virtual ~QbertMovingState() = default;

		virtual void OnEnter() override;
		virtual std::unique_ptr<QbertState> Update() override { return nullptr; };
		virtual std::unique_ptr<QbertState> FixedUpdate() override;

	private:
		FacingDirection m_facingDirection{ FacingDirection::Left_Down };
		glm::vec2 m_goalPos{ 0.f,0.f };
		const float m_speed{ 0.02f };
	};

}
