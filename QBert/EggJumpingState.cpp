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
	auto grid = m_pCoilyObject.lock().get()->GetComponentByType<dae::IsometricGridPositionComponent>()->GetGrid();
	glm::vec2 goal_pos = m_pCoilyObject.lock().get()->GetComponentByType<dae::IsometricGridPositionComponent>()->GetIsometricPosition();
	const int rnd_x = -(rand() % 2);
	const int rnd_y = (rnd_x == -1) ? 0 : -1;
	goal_pos.x += rnd_x;
	goal_pos.y += rnd_y;
	while (m_pCoilyObject.lock()->GetComponentInParents<)
	{

	}


	m_pGoalPosition = std::make_unique<IsometricGridPosition>();
}

std::unique_ptr<CoilyState> EggJumpingState::FixedUpdate()
{
	//Update pos
		
	if (m_pCoilyObject.lock().get()->GetComponentByType<dae::IsometricGridPositionComponent>()->GetIsometricPosition() == m_pGoalPosition->position)
	{
		return std::make_unique<EggStaticState>(m_pCoilyObject);
	}
	return nullptr;
}
