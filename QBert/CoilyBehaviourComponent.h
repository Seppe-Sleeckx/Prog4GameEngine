#pragma once
#include "Component.h"
#include "IsometricGrid.h"
#include "CoilyState.h"

namespace qbert
{
	class CoilyBehaviourComponent final : public dae::Component
	{
	public:
		CoilyBehaviourComponent(std::shared_ptr<dae::GameObject> pOwner, std::weak_ptr<Piramid> pPiramid);
		virtual ~CoilyBehaviourComponent() = default;
		virtual void Update() override;
		virtual void FixedUpdate() override;

	private:
		void ChangeState(std::unique_ptr<CoilyState> pNewState);
		std::unique_ptr<CoilyState> m_pState;
	};
}
