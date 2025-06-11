#pragma once
#include "Component.h"
#include "Piramid.h"
#include "QbertState.h"
namespace qbert
{
	class QbertBehaviourComponent final : public dae::Component
	{
	public:
		QbertBehaviourComponent(std::shared_ptr<dae::GameObject> pOwner, std::weak_ptr<Piramid> pPiramid);
		virtual ~QbertBehaviourComponent() = default;
		virtual void Update() override;
		virtual void FixedUpdate() override;

	private:
		void ChangeState(std::unique_ptr<QbertState> pNewState);
		std::unique_ptr<QbertState> m_pState;
	};
}
