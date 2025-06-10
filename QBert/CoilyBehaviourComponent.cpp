#include "CoilyBehaviourComponent.h"
#include "IsometricGridPositionComponent.h"
#include "EggFallingState.h"
#include "GameObject.h"
using namespace qbert;

CoilyBehaviourComponent::CoilyBehaviourComponent(std::shared_ptr<dae::GameObject> pOwner) : dae::Component(pOwner)
{
	ChangeState(std::move(std::make_unique<qbert::EggFallingState>(pOwner)));
}

void CoilyBehaviourComponent::Update()
{
	auto new_state = m_pState->Update();
	if (new_state != nullptr)
		ChangeState(std::move(new_state));
}

void CoilyBehaviourComponent::FixedUpdate()
{
	auto new_state = m_pState->FixedUpdate();
	if (new_state != nullptr)
		ChangeState(std::move(new_state));
}

void CoilyBehaviourComponent::ChangeState(std::unique_ptr<CoilyState> pNewState)
{
	m_pState = std::move(pNewState);
	m_pState->OnEnter();
}