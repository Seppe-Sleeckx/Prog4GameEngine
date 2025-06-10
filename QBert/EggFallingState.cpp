#include "EggFallingState.h"
#include "IsometricGridPositionComponent.h"
#include "EggStaticState.h"
#include "Texture2DRenderer.h"
#include "GameObject.h"
#include "GameTime.h"
using namespace qbert;

void EggFallingState::OnEnter()
{
	auto grid = m_pCoilyObject.lock().get()->GetComponentByType<dae::IsometricGridPositionComponent>()->GetGrid();
	const int rnd_x = rand()%2;
	const int rnd_y = (rnd_x == 1) ? 0 : 1;
	glm::vec2 goal_pos{ rnd_x, rnd_y };
	m_pGoalPosition = std::make_unique<IsometricGridPosition>(goal_pos, grid); 

	glm::vec2 start_pos{ rnd_x-1.5f, rnd_y-1.5f};
	m_pCoilyObject.lock().get()->GetComponentByType<dae::IsometricGridPositionComponent>()->SetIsometricPosition(start_pos);

	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(m_spriteSrcRect);
}

std::unique_ptr<CoilyState> EggFallingState::FixedUpdate()
{
	//m_speed += static_cast<float>(9.81f * dae::Time::GetInstance().GetFixedDeltaTime()) * 0.01f;
	m_speed += 0.001f;
	//m_speed = 0.01f;
	m_pCoilyObject.lock().get()->GetComponentByType<dae::IsometricGridPositionComponent>()->MoveTowards(m_pGoalPosition->position, m_speed);
	if(m_pCoilyObject.lock().get()->GetComponentByType<dae::IsometricGridPositionComponent>()->GetIsometricPosition() == m_pGoalPosition->position)
		return std::make_unique<EggStaticState>(m_pCoilyObject);

	return nullptr;
}
