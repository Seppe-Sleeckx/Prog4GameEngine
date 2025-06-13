#include "QbertBehaviourComponent.h"
#include "IsometricGridPositionComponent.h"
#include "QbertStaticState.h"
#include "GameObject.h"
using namespace qbert;

QbertBehaviourComponent::QbertBehaviourComponent(std::shared_ptr<dae::GameObject> pOwner, std::weak_ptr<Piramid> pPiramid) : dae::Component(pOwner)
{
	pOwner->GetComponentByType<IsometricGridPositionComponent>()->SetIsometricPosition(glm::vec2{ 0.f,0.f });
	ChangeState(std::move(std::make_unique<qbert::QbertStaticState>(pOwner, std::move(pPiramid), FacingDirection::Left_Down)));
}

void QbertBehaviourComponent::Update()
{
	auto new_state = m_pState->Update();
	if (new_state != nullptr)
		ChangeState(std::move(new_state));
}

void QbertBehaviourComponent::FixedUpdate()
{
	auto new_state = m_pState->FixedUpdate();
	if (new_state != nullptr)
		ChangeState(std::move(new_state));
}

void QbertBehaviourComponent::ChangeState(std::unique_ptr<QbertState> pNewState)
{
	if(m_pState.get() != nullptr)
		m_pState->OnExit();

	m_pState = std::move(pNewState);
	m_pState->OnEnter();
}