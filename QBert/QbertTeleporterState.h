#pragma once
#include "QbertState.h"
#include "GameObject.h"
namespace qbert
{
	class QbertTeleporterState final : public QbertState
	{
	public:
		QbertTeleporterState(std::weak_ptr<dae::GameObject> pQbertObject, std::weak_ptr<Piramid> pPiramid) : QbertState(std::move(pQbertObject), std::move(pPiramid)) {}

		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual std::unique_ptr<QbertState> Update() override { return nullptr; };
		virtual std::unique_ptr<QbertState> FixedUpdate() override;

		virtual QbertStateType GetType() override { return QbertStateType::Teleporter; }
	private:
		const glm::vec2 m_goalPos{ -1.f,-1.f };
		const float m_speed{ 2.f };

		glm::vec3 m_originalScale{ 1.f,1.f,1.f };
	};
}
