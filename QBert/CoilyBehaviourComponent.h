#pragma once
#include "Component.h"
#include "IsometricGrid.h"
#include "CoilyState.h"

namespace dae
{
	class CoilyBehaviourComponent final : public Component
	{
	public:
		CoilyBehaviourComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~CoilyBehaviourComponent() = default;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() const override;

	private:
		std::unique_ptr<CoilyState> m_pState;
	};
}
