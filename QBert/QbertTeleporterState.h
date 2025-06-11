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
		virtual std::unique_ptr<QbertState> Update() override { return nullptr; };
		virtual std::unique_ptr<QbertState> FixedUpdate() override;
	private:
		glm::vec2 m_goalPos{ 0.f,0.f };
	};
}
