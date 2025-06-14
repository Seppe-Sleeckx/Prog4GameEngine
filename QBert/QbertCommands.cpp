#include "QbertCommands.h"
#include "QbertMovingState.h"
#include "QbertStaticState.h"
#include "QbertBehaviourComponent.h"
#include "HealthComponent.h"
#include "CubeColorComponent.h"
#include "LevelManager.h"
#include "SceneManager.h"

using namespace qbert;

void MoveQbertCommand::Execute()
{
	auto behaviour_component = m_pQbert.lock()->GetComponentByType<QbertBehaviourComponent>();

	if (behaviour_component->GetState()->GetType() != QbertState::QbertStateType::Static)
		return;

	auto piramid = behaviour_component->GetState()->GetPiramid();
	auto moving_state = std::make_unique<QbertMovingState>(m_pQbert, piramid, m_movingDirection);
	behaviour_component->ChangeState(std::move(moving_state));
}

void QbertTakeDamageCommand::Execute()
{
	auto health_component = m_pQbert.lock()->GetComponentByType<HealthComponent>();

	health_component->TakeDamage(m_amountOfDamage);

	//Disable movement commands?

	//Reset level
}

void ChangeCubeColorCommand::Execute()
{
	//increase score

	auto color_component = m_pCube->GetComponentByType<qbert::CubeColorComponent>();
	color_component->SetNextColor();

	if (LevelManager::GetInstance().GetPiramid()->IsPiramidCompleted())
	{
		//Disable bindings
		//Play animation
		//start new scene
		LevelManager::GetInstance().StartNextRound();
	}
}

void SkipRoundCommand::Execute()
{
	LevelManager::GetInstance().StartNextRound();
}
