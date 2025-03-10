#include "PlayerCommands.h"
#include "MovementComponent.h"
using namespace dae;

void MovePlayerCommand::Execute()
{
	m_player->GetComponentByType<MovementComponent>()->Move(glm::vec3(m_direction.x, m_direction.y, 0.f));
}

