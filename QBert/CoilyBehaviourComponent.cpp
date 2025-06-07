#include "CoilyBehaviourComponent.h"
#include "IsometricGridPositionComponent.h"
#include "EggStaticState.h"
#include "GameObject.h"
using namespace dae;

CoilyBehaviourComponent::CoilyBehaviourComponent(std::shared_ptr<GameObject> pOwner) : Component(pOwner),
	m_pState{ std::make_unique<EggStaticState>(pOwner)}
{}

void CoilyBehaviourComponent::Update()
{
	auto new_state = m_pState->Update();
	if (new_state != nullptr)
		m_pState = std::move(new_state);
}

void CoilyBehaviourComponent::FixedUpdate()
{
	auto new_state = m_pState->FixedUpdate();
	if (new_state != nullptr)
		m_pState = std::move(new_state);
}

void CoilyBehaviourComponent::Render() const
{
	m_pState->Render();
}