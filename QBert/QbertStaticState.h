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
		virtual std::unique_ptr<QbertState> Update() override;
		virtual std::unique_ptr<QbertState> FixedUpdate() override { return nullptr; };

		virtual QbertStateType GetType() override { return QbertStateType::Static; }
	private:
		FacingDirection m_facingDirection{ FacingDirection::Left_Down };
		const float m_stunnedTime{ 2.f };
		float m_stunnedTimer{ 0.f };
		bool m_stunned{ false };
		std::weak_ptr<dae::GameObject> m_textBalloon{};
	};

}