#pragma once
#include "QbertState.h"
#include <memory>
#include "StateHelpers.h"
#include <chrono>

namespace qbert
{
	class QbertStaticState final : public QbertState
	{
	public:
		QbertStaticState(std::weak_ptr<dae::GameObject> pQbertObject, std::weak_ptr<Piramid> pPiramid, FacingDirection move_direction) : QbertState(std::move(pQbertObject), std::move(pPiramid)), m_facingDirection{ move_direction } {}
		virtual ~QbertStaticState() = default;

		virtual void OnEnter() override;
		virtual std::unique_ptr<QbertState> Update() override { return nullptr; };
		virtual std::unique_ptr<QbertState> FixedUpdate() override { return nullptr; };

		virtual QbertStateType GetType() override { return QbertStateType::Static; }
	private:
		FacingDirection m_facingDirection{ FacingDirection::Left_Down };
	};

}