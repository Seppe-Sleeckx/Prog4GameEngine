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
		virtual std::unique_ptr<QbertState> Update() override;
		virtual std::unique_ptr<QbertState> FixedUpdate() override;

		virtual QbertStateType GetType() override { return QbertStateType::Falling; }

	private:
		const FacingDirection m_facingDirection;
		const std::chrono::seconds m_fallTime{ 1 }; //falls for x amount of seconds before calling reset
		std::chrono::duration<float> m_elapsedTime{};
		float m_fallSpeed{ 1.f };
	};
}

