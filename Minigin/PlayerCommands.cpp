#include "PlayerCommands.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
using namespace dae;

void MovePlayerCommand::Execute()
{
	m_player->GetComponentByType<MovementComponent>()->Move(glm::vec3(m_direction.x, m_direction.y, 0.f));
}

void TakeDamageCommand::Execute()
{
	m_player->GetComponentByType<HealthComponent>()->TakeDamage(DAMAGE_AMOUNT);
}
