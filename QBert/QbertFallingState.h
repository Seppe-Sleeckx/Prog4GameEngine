#pragma once
#include "QbertState.h"
#include "StateHelpers.h"
#include <chrono>
namespace qbert
{
	class QbertFallingState final : public QbertState
	{
	public:
		QbertFallingState(std::weak_ptr<dae::GameObject> pQbertObject, std::weak_ptr<Piramid> pPiramid, FacingDirection facing_direction) : QbertState(std::move(pQbertObject), std::move(pPiramid)), m_facingDirection{ facing_direction } {}

		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual std::unique_ptr<QbertState> Update() override { return nullptr; }
		virtual std::unique_ptr<QbertState> FixedUpdate() override;

		virtual QbertStateType GetType() override { return QbertStateType::Falling; }

	private:
		const FacingDirection m_facingDirection;
		float m_fallSpeed{ 2.f };
		glm::vec2 m_goalPos;
	};
}

