#include "EggJumpingState.h"
#include "EggStaticState.h"
#include "Texture2DRenderer.h"
#include "GameObject.h"
using namespace qbert;

void EggJumpingState::OnEnter()
{
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(m_spriteSrcRect);

	//Calculate goal position
	auto grid = m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetGrid();
	glm::vec2 goal_pos = m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition();
	const int rnd_x = (rand() % 2);
	const int rnd_y = (rnd_x == 1) ? 0 : 1;
	goal_pos.x += rnd_x;
	goal_pos.y += rnd_y;
	
	if (m_pPiramid.lock()->GetCubeAtIsometricPos(goal_pos) == nullptr)
	{
		goal_pos = m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition();
		goal_pos.x += rnd_y;
		goal_pos.y += rnd_x;
	}

	m_pGoalPosition = std::make_unique<IsometricGridPosition>(goal_pos, grid);
}

std::unique_ptr<CoilyState> EggJumpingState::FixedUpdate()
{
	//Update pos
	m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->MoveTowards(m_pGoalPosition->position, m_speed);

	if (m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition() == m_pGoalPosition->position)
	{
		return std::make_unique<EggStaticState>(m_pCoilyObject, m_pPiramid);
	}
	return nullptr;
}
